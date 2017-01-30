#include <QQmlEngine>
#include <QtWidgets>
#include <QQmlComponent>
#include <QFileDialog>
#include <QDebug>
#include <QColor>

#include <iterator>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

#include "imageManager.h"

#include <tool/circleTool.h>

ImageManager::ImageManager(QQmlApplicationEngine* engine)
    : QObject(0)
{
    this->engine = engine;
    //this->root = engine->rootContext();
    //this->textAlgorithManager = root->findChild("textAlgorithmManager");


    nbPreviewsDisplayed = 3;
    nbPreviewsMax = 10;
    selectionAlpha = 1.0/3.0;
    algorithmManager = AlgorithmManager();
    layers = Layers();
    colors = Colors();

    previews = Previews();
    previewLayers = Layers();
    previewCreators = PreviewCreators();

    previews.resize(nbPreviewsMax);
    previewLayers.resize(nbPreviewsMax);
    previewCreators.resize(nbPreviewsMax);

    updateBackMatrix(Layer(1, 1, CV_8UC3));

    rebasePreviews(&backMatrix, 1, 1);

    //QImage base = new QImage(1, 1, QImage::Format_RGBA8888);


    qDebug() << "creator instantiated";
    initPreviewCreators();
    qDebug() << "creators set";

    drawingTools = DrawingTools();
    drawingTools.push_back(new CircleTool());

    //resetPreviews();

    //setImage(initialImage());
    //loadFile("C:/Users/corentin/Pictures/test.png");
    //loadFile("C:/Users/corentin/Pictures/gfx/Antolach.png");
    //loadFile("C:/Users/corentin/Pictures/baseFond2.png");
}

void ImageManager::initPreviewCreators() {
    // initiating with default values
    PreviewCreator c = [&](Layer* RGBMatrix, Layer* mask) {};
    for(int i=0; i<nbPreviewsMax; ++i) {
        previewCreators[i] = c;
    };


    previewCreators[0] = [&](Layer* RGBMatrix, Layer* mask) {
        QObject* parameters = new QObject();
        parameters->setObjectName("niblack");
        algorithmManager.applyText(RGBMatrix, mask, parameters);
        delete parameters;
    };
    previewCreators[1] = [&](Layer* RGBMatrix, Layer* mask) {
        QObject* parameters = new QObject();
        parameters->setObjectName("sauvola");
        algorithmManager.applyText(RGBMatrix, mask, parameters);
        delete parameters;
    };
    previewCreators[2] = [&](Layer* RGBMatrix, Layer* mask) {
        QObject* parameters = new QObject();
        parameters->setObjectName("threshold");
        algorithmManager.applyText(RGBMatrix, mask, parameters);
        delete parameters;
    };
    previewCreators[3] = [&](Layer* RGBMatrix, Layer* mask) {
        QObject* parameters = new QObject();
        parameters->setObjectName("adaptiveThreshold");
        algorithmManager.applyText(RGBMatrix, mask, parameters);
        delete parameters;
    };
}


void ImageManager::isolateLines() {
    int chan = mainMatrix.channels();
    int height = mainMatrix.rows;
    int width = mainMatrix.cols * chan;
    int size = width * height;
    uchar* l;
    int i, j;

    int nbLayers = layers.size();
    Layer* layer;

    int tops[nbLayers];
    int bottoms[nbLayers];

    int order[nbLayers];
    int orderIndex = 0;

    bool isOrdered[nbLayers];

    for(j=0; j<nbLayers; ++j) {
        isOrdered[j] = false;
        order[j] = -1;
        tops[j] = -1;
        bottoms[j] = -1;
    }

    for(i=0; i<size; i+=chan) {
        for(j=0; j<nbLayers; ++j) {
            layer = layers[j];
            l = layer->ptr();

            if(isOrdered[j]) {
                if(l[i] || l[i+1] || l[i+2]) {
                    bottoms[j] = i;
                }
            } else {
                if(l[i] || l[i+1] || l[i+2]) { //non transparent pixel
                    //adding layer to order
                    isOrdered[j] = true;
                    qDebug() << "bound" << orderIndex << "is for layer" << j << "( top is" << (i/width) << ")";
                    order[orderIndex++] = j;
                    tops[j] = i;
                } //transparent pixel
            }
        }
    }

    for(j=0; j<nbLayers; ++j) {
        tops[j] /= width;
        bottoms[j] /= width;
        qDebug() << "bound" << tops[j] << "->" << bottoms[j];
    }

    qDebug() << "bounds found";

    cv::Vec2i bounds[nbLayers];

    for(j=0; j<nbLayers; ++j) {
        bounds[j] = cv::Vec2i(tops[order[j]], bottoms[order[j]]);
        qDebug() << "bounds" << j << " is [" << bounds[j][0] << "," << bounds[j][1] << "]";
    }

    qDebug() << "bounds ordered";

    int sep = 50;
    int rows = bounds[0][1] - bounds[0][0] + 1;
    for(j=1; j<nbLayers; ++j) {
        rows += sep;
        rows += bounds[j][1] - bounds[j][0] + 1;
    }

    qDebug() << "line matrix size found (" << rows << "rows," << mainMatrix.cols << "cols)";

    Layer* ll = new Layer(Layer::zeros((int)rows, (int)mainMatrix.cols, CV_8UC3));
    uchar* lp = ll->ptr();
    for(i=0; i<rows*mainMatrix.cols*chan; i+=chan) {
        lp[i  ] = 0xFF;
        lp[i+1] = 0x25;
        lp[i+2] = 0x68;
    }

    qDebug() << "line matrix created (" << rows << "rows," << mainMatrix.cols << "cols)";

    int x, y, rx, ry;

    rx = 0;
    ry = 0;
    cv::Vec3b vec;
    for(j=0; j<nbLayers; ++j) {
        for(y=bounds[j][0]; y<=bounds[j][1]; ++y) {
            for(x=0; x<ll->cols; ++x) {
                vec = (*layers[j]).at<cv::Vec3b>(y, x);
                if(vec[0] || vec[1] || vec[2])
                    ll->at<cv::Vec3b>(ry+y-bounds[j][0], rx+x) = mainMatrix.at<cv::Vec3b>(y, x);
            }
        }
        ry += sep + bounds[j][1] - bounds[j][0] + 1;

        qDebug() << "layer" << j << "painted";
    }

    qDebug() << "layers painted";

    updateBackMatrix(*ll);

    qDebug() << "line matrix set as main";

    imageUpdate();

    qDebug() << "display refresh requested";

}

void ImageManager::shiftPreviewsLeft() {
    int i = 0;
    QImage* first = previews[i];
    while(i<nbPreviewsMax) {
        previews[i] = previews[i+1];
        ++i;
    }
    previews[nbPreviewsMax-1] = first;
    previewsUpdate();
}

void ImageManager::shiftPreviewsRight() {
    int i = nbPreviewsMax-1;
    QImage* last = previews[i];
    while(i) {
        previews[i] = previews[i-1];
        --i;
    }
    previews[0] = last;
    previewsUpdate();

    /*QImage* first = previews.front();
    previews.erase(previews.begin());
    previews.push_back(first);
    previewUpdate();*/
}

int ImageManager::getPreviewWidth() {return previewWidth;}
int ImageManager::getPreviewHeight() {return previewHeight;}
int ImageManager::getSelectedPreviewID() {return selectedPreviewID;}
int ImageManager::getMaxPreviewX() {return previewReference->cols-previewWidth;}
int ImageManager::getMaxPreviewY() {return previewReference->rows-previewHeight;}
int ImageManager::getPreviewX() {return std::round(getMaxPreviewX()*previewX);}
int ImageManager::getPreviewY() {return std::round(getMaxPreviewY()*previewY);}




QImage ImageManager::initialImage() {
    QImage init = QImage(200, 200, QImage::Format_RGBA8888);
    QPainter paint;
    paint.begin(&init);
    paint.fillRect(
                QRectF(0, 0, init.width(), init.height()),
                QColor(0, 0, 0)
                );
    paint.setPen(QColor(255, 255, 255));
    paint.setBrush(QColor(255, 255, 255));
    paint.drawText(QPointF(10, 10), "NO IMAGE");
    return init;
}

DrawingTool* ImageManager::getDrawingTool(QString name) {
    DrawingTool* t;
    for(unsigned i=0; i<drawingTools.size(); ++i) {
        t = drawingTools[i];
        if(t->getName() == name)
            return t;
    }
    return NULL;
}

// conversion found at http://stackoverflow.com/a/36956273
cv::Scalar colorToscalar(QColor color) {
    int r,g,b;
    color.getRgb(&r, &g, &b);
    return cv::Scalar(b,g,r); // swap RGB-->BGR
}

// conversion found at http://stackoverflow.com/a/36956273
QColor scalarToColor(cv::Scalar color) {
    return QColor(color[2],color[1],color[0]); // swap RGB-->BGR
}

void ImageManager::mouseDown(int x, int y, QString toolName, QColor color, QObject* sizeParameters) {
    Layer* layer = getLayer(color);
    DrawingTool* tool = getDrawingTool(toolName);
    cv::Scalar scalar = colorToscalar(color);

    //qDebug() << toolName;
    //std::cout << mainMatrix << std::endl;
    //std::cout << render << std::endl;

    if(tool == NULL)
        return;

    tool->draw(layer, x, y, scalar, sizeParameters);
    blendAndUpdate(&mainMatrix, &render);
}

Layer* ImageManager::mainClone() {
    return new Layer(mainMatrix.clone());
}

void ImageManager::updateBackMatrix(Layer layer) {
    backMatrix = layer;
    mainMatrix = backMatrix.clone();
    render = backMatrix.clone();
    mainImage = QImage(
                render.data,
                render.cols,
                render.rows,
                static_cast<int>(render.step),
                QImage::Format_RGB888);
}

bool ImageManager::loadFile(const QString &fileName) {
    Layer l = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);
    qDebug() << "read";
    backMatrix = Layer(l.rows, l.cols, CV_8UC3);
    cv::cvtColor(l, backMatrix, cv::COLOR_RGBA2BGR);

    updateBackMatrix(backMatrix);

    //mainImage = mainImage.rgbSwapped();
    qDebug() << "image";

    imageReady = false;
    resetLayers();
    qDebug() << "layers";
    rebasePreviews(&backMatrix, 80, 120);
    applyPreviews();
    qDebug() << "previews";
    blendAndUpdate(&mainMatrix, &render);
    qDebug() << "blend";

    return true;
}

void ImageManager::resetLayers() {
    for(int i=0; i<layers.size(); ++i) {
        delete(layers[i]);
    }
    layers.clear();
    colors.clear();
}

Layer* ImageManager::getLayer(QColor color) {
    for(int i=0; i<colors.size(); ++i) {
        if(color == colors[i])
            return layers[i];
    }
    colors.push_back(color);

    Layer* layer = new Layer(Layer::zeros(mainMatrix.rows, mainMatrix.cols, CV_8UC3));
    layers.push_back(layer);
    return layer;
}


void ImageManager::rebasePreviews(Layer* reference, int width, int height) {
    previewReference = reference;

    width = std::min(width, reference->cols);
    height = std::min(height, reference->rows);


    if(previewWidth!=width || previewHeight!=height) {
        previewWidth = width;
        previewHeight = height;

        QImage* image;
        Layer* layer;
        Layer roi = (*reference)(cv::Rect(getPreviewX(), getPreviewY(), previewWidth, previewHeight));
        for(int i=0; i<nbPreviewsMax; ++i) {
            delete(previews[i]);
            delete(previewLayers[i]);
            layer = new Layer(roi.clone());
            image = new QImage(
                        layer->data,
                        layer->cols,
                        layer->rows,
                        static_cast<int>(layer->step),
                        QImage::Format_RGB888);
            previewLayers[i] = layer;
            previews[i] = image;
        }
        previewSizeChanged();
    } else {
        rebasePreviews();
    }
}

void ImageManager::rebasePreviews() {
    Layer roi = (*previewReference)(cv::Rect(getPreviewX(), getPreviewY(), previewWidth, previewHeight));
    for(int i=0; i<nbPreviewsMax; ++i) {
        roi.copyTo(*previewLayers[i]);
    }
}

void ImageManager::movePreviews(float x, float y) {
    qDebug() << x << y;
    if(previewX!=x || previewY!=y) {
        previewX = x;
        previewY = y;
        rebasePreviews();
        applyPreviews();

        /*Layer preview = Layer(previewHeight, previewWidth, CV_8UC3);


        Layer(rows, cols, CV_8UC3, new uchar[size], step);*/

    }

}

/*void ImageManager::applyNiblack(Layer* layer, Layer* mask) {
    QObject* parameters = new QObject();
    parameters->setObjectName("niblack");
    algorithmManager.applyText(layer, mask, parameters);
}*/

void ImageManager::applyPreviews() {
    const int max = nbPreviewsMax;
    for(int i=0; i<max; ++i) {
        previewCreators[(selectedPreviewID+i)%max](previewLayers[i], getMaskLayer());
    }


    /*previews.clear();
    addPreview("niblack");
    addPreview("sauvola");
    addPreview("adaptiveThreshold");*/

    previewsUpdate();



    /*QImage* i;
    Layer* l;
    QObject* previews = root->findChild("previews");

    l = new Layer(mainMatrix.clone());*/
    //textAlgorithManager->setProperty("algorithmName", "niblack");

    /*QObject* preview1 = previews->findChild("preview1");
    if(preview1 == NULL) {
        preview1 = new QObject(previews);
    }*/

}


void ImageManager::blend(Layer* in, Layer* out) {

    in->copyTo(*out);

    int chan = in->channels();
    int height = in->rows;
    int width = in->cols * chan;
    int size = width * height;
    uchar* r = out->ptr();
    uchar* l;
    float a = selectionAlpha;
    float b = 1.0f-a;
    int i;
    for(Layer* layer : layers) {
        l = layer->ptr();
        for(i=0; i<size; i+=chan) {
            if(l[i] || l[i+1] || l[i+2]) { //non transparent pixel
                r[i  ] = r[i  ]*b + l[i  ]*a;
                r[i+1] = r[i+1]*b + l[i+1]*a;
                r[i+2] = r[i+2]*b + l[i+2]*a;
            } //transparent pixel
        }
    }
    //std::cout << mainMatrix << std::endl;
    //std::cout << render << std::endl;
}

void ImageManager::blendAndUpdate(Layer* in, Layer* out) {
    blend(in, out);
    imageUpdate();
    previewsUpdate();

    /*QObject* object = new QObject();
    object->setProperty("radius", 200);

    mouseDown(100, 100, 0, "pinceau", new QColor(0x0000FF), object);*/

    //qDebug() << "--- layers blending";
    //qDebug() << "[V] layers blending";

    /*qDebug() << "--- copying matrix data into image";
    int size = render.total() * render.elemSize();
    std::memcpy(mainImage.bits(), render.data, size);
    qDebug() << "[V] copying matrix data into image";*/

    //qDebug() << "--- image update";
    //qDebug() << "[V] image update";
}

/*void ImageManager::resetDisplay(Layer* in, Layer* in, Layer* out) {
    backMatrix.copyTo(mainMatrix);
    blendAndUpdate(&mainMatrix, &render);
}*/

void ImageManager::resetDisplayInside(Layer* in, Layer* out, Layer* mask) {
    uchar* m = mask->ptr();
    uchar* o = out->ptr();
    uchar* i = in->ptr();
    int chan = mask->channels();
    int width = mask->cols * chan;
    int height = mask->rows;
    int size = width*height;
    int y = 0;

    for(int x=0; x<size; x+=chan) {
        if(m[x] | m[x+1] | m[x+2]) {
            o[x  ] = i[x  ];
            o[x+1] = i[x+1];
            o[x+2] = i[x+2];
        }
        ++y;
    }
}

void ImageManager::applyText(QObject* parameters) {
    Layer* mask = getMaskLayer();
    resetDisplayInside(&backMatrix, &mainMatrix, mask);
    algorithmManager.applyText(&mainMatrix, mask, parameters);
    blendAndUpdate(&mainMatrix, &render);
}

Layer* ImageManager::getMaskLayer() {
    const int rows = mainMatrix.rows;
    const int cols = mainMatrix.cols;
    if(layers.empty()) {
        if(&mask==NULL || cols != mask.cols || rows != mask.rows) {
            mask = Layer::ones(rows, cols, CV_8UC3);
            qDebug() << "No default mask found : created one";
        }
        qDebug() << "Default mask found";
        return &mask;
    }
    qDebug() << "Base layer found";
    return layers[0];
}

void ImageManager::applyRefine(QObject* parameters) {
    algorithmManager.applyRefine(&mainMatrix, layers[0], parameters);
    blendAndUpdate(&mainMatrix, &render);
}

void ImageManager::applyLine(QObject* parameters) {
    algorithmManager.applyLine(&mainMatrix, layers[0], parameters);
    blendAndUpdate(&mainMatrix, &render);
}

QImage ImageManager::getImage() {
    return mainImage;
}

void ImageManager::addPreview(QString textAlgoName) {

    Layer* layer = new Layer(mainMatrix.clone());
    qDebug() << "preview matrix created (" + textAlgoName + ")";

    QObject* parameters = engine->rootObjects().first()->findChild<QObject*>(textAlgoName);
    qDebug() << "parameters found";
    Layer* mask = getMaskLayer();
    qDebug() << "mask found";

    algorithmManager.applyText(layer, mask, parameters);
    qDebug() << "algorithm applied";
    QImage* image = new QImage(
                layer->data,
                layer->cols,
                layer->rows,
                static_cast<int>(layer->step),
                QImage::Format_RGB888);
    qDebug() << "preview image created (" + textAlgoName + ")";
    previews.push_back(image);
    qDebug() << "preview pushed to list";
}

QImage ImageManager::getPreview(int id) {
    return *previews[id];
}











void ImageManager::updateMatrixes() {
    const int rows = mainImage.height();
    const int cols = mainImage.width();
    size_t size = mainImage.byteCount();
    const int step = 24;
    if(
            &mainMatrix==NULL ||
            cols != mainMatrix.cols ||
            rows != mainMatrix.rows) {

        mainMatrix = Layer(rows, cols, CV_8UC3, new uchar[size], step);
        //render = Layer(rows, cols, CV_8UC3, new uchar[size], step);
    }
}


void ImageManager::setImage(Layer mat) {

    mainMatrix = mat;
    //std::cout << mainMatrix << std::endl;

    qDebug() << "--- initializing layers";
    resetLayers();
    qDebug() << "[V] initializing layers";

}

void ImageManager::setImage(QImage image) {

    qDebug() << "--- new image";
    mainImage = image.convertToFormat(QImage::Format_RGB888);
    qDebug() << "[V] new image";


    qDebug() << "--- updating matrix";
    updateMatrixes();
    qDebug() << "[V] updating matrix";


    qDebug() << "--- copying image data into matrix";
    int size = mainMatrix.total() * mainMatrix.elemSize();
    uchar* src = mainImage.bits();
    uchar* dest = mainMatrix.data;
    std::memcpy(dest, src, size);
    qDebug() << "[V] copying image data into matrix";

    std::cout << size << std::endl;
    std::cout << mainMatrix.total() << std::endl;
    std::cout << mainMatrix.elemSize() << std::endl;
    std::cout << mainMatrix.step << std::endl;
    std::cout << mainMatrix << std::endl;

    //imageToMat(mainImage, &mainMatrix);
    qDebug() << "--- initializing layers";
    resetLayers();
    qDebug() << "[V] initializing layers";
}

/*void ImageManager::blend() {
    float beta = 1.0 - selectionAlpha;
    qDebug() << selectionAlpha;

    qDebug() << "--- --- cloning matrix";
    //render = mainClone();
    qDebug() << "--- [V] cloning matrix";

    qDebug() << "--- --- layers weighting";
    cv::addWeighted(mainMatrix, selectionAlpha, *layers[0], beta, 0.0, render);
    qDebug() << "--- [V] layers weighting";
}*/

void ImageManager::imageToMat(QImage image, Layer* matrix) {
    qDebug() << "--- image to matrix";
    /*Layer* mat = new Layer(
                image.height(),
                image.width(),
                CV_8UC3,
                image->bits(),
                image->bytesPerLine()
                );*/
    qDebug() << "[V] image to matrix";
    //return mat;
}

void ImageManager::matToImage(Layer matrix, QImage* image) {
    qDebug() << "--- matrix to image";
    /*QImage image = new QImage(
                mat->data,
                mat->cols,
                mat->rows,
                static_cast<int>(mat->step),
                QImage::Format_RGB888
                );*/
    qDebug() << "[V] matrix to image";
    //return image;
    //return image.rgbSwapped();
}

Layer* ImageManager::RGBALayer() {
    return new Layer(mainMatrix.rows, mainMatrix.cols, CV_8UC4);
}

Layer* ImageManager::RGBLayer() {
    return new Layer(mainMatrix.rows, mainMatrix.cols, CV_8UC3);
}

void ImageManager::onImageUpdate() {
    qDebug() << "[V] image update";
}

static void completeFill(Layer l) {
    for(int y=0; y<l.rows; ++y) {
        for(int x=0; x<l.cols; ++x) {
            l.at<RGB>(y, x)[0] = 0;
            l.at<RGB>(y, x)[1] = 0;
            l.at<RGB>(y, x)[2] = 255;
        }
    }
}

static void rectFill(Layer l) {
    for(int y=l.rows/4; y<3*l.rows/4; ++y) {
        for(int x=l.cols/4; x<3*l.cols/4; ++x) {
            l.at<RGB>(y, x)[0] = 0;
            l.at<RGB>(y, x)[1] = 0;
            l.at<RGB>(y, x)[2] = 255;
        }
    }
}

static void fooFill(Layer l) {

    std::srand(std::time(0)); // use current time as seed for random generator

    //RNG rng();
    //rng.fill(matrix2xN, cv::RNG::NORMAL, mean, sigma);
    int wasTrue = false;
    for(int y=0; y<l.rows; ++y) {
        for(int x=0; x<l.cols; ++x) {
            if(wasTrue ? std::rand()%2 : 1-std::rand()%2) {
                wasTrue = true;
                l.at<RGB>(y, x)[0] = 0;
                l.at<RGB>(y, x)[1] = 0;
                l.at<RGB>(y, x)[2] = 255;
            } else {
                wasTrue = false;
            }
        }
    }
}


int ImageManager::getDefaultImageWidth() {
    return 100;
}

int ImageManager::getDefaultImageHeight() {
    return 100;
}

void ImageManager::add(QObject *image, QString source) {
    /* QQmlEngine engine;
    QQmlComponent component(&engine, "GeneaImage.qml");
    QObject *object = component.create();*/
    qDebug() << "added image " << source;

    image->setProperty("x", 200);
    image->setProperty("y", 150);
    image->setProperty("width", getDefaultImageWidth());
    image->setProperty("height", getDefaultImageHeight());
    image->setProperty("source", source);
}


static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations =
                QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

        dialog.setDirectory(
                    picturesLocations.isEmpty()
                    ? QDir::currentPath()
                    : picturesLocations.last()
                      );
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes =
            acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes()
            : QImageWriter::supportedMimeTypes();

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("png");
}

void ImageManager::open()
{
    QFileDialog dialog(QApplication::activeWindow(), tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (
           dialog.exec() == QDialog::Accepted &&
           !loadFile(dialog.selectedFiles().first())
           ) {
        qDebug() << "dialog opened at "+ dialog.selectedFiles().first();
    }
}

void ImageManager::saveAs()
{
    QFileDialog dialog(QApplication::activeWindow(), tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (
           dialog.exec() == QDialog::Accepted &&
           !saveFile(dialog.selectedFiles().first())
           ) {}
}





bool ImageManager::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(mainImage)) {
        QMessageBox::information(QApplication::activeWindow(), QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    //statusBar()->showMessage(message);
    return true;
}

void ImageManager::print()
{
    //Q_ASSERT(imageLabel->pixmap());
}

void ImageManager::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(mainImage);
#endif // !QT_NO_CLIPBOARD
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void ImageManager::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        //statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        setImage(newImage);
        QApplication::activeWindow()->setWindowFilePath(QString());
        //const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
        //        .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        //statusBar()->showMessage(message);
    }
#endif // !QT_NO_CLIPBOARD
}

void ImageManager::zoomIn()
{
    //scaleImage(1.25);
}

void ImageManager::zoomOut()
{
    //scaleImage(0.8);
}

/*void imagemanager::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void imagemanager::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}*/

