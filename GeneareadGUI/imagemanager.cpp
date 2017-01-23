#include <QQmlEngine>
#include <QtWidgets>
#include <QQmlComponent>
#include <QFileDialog>
#include <QDebug>

#include <iterator>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "imageManager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent) {
    count = 0;
    selectionAlpha = 1.0/3.0;
    selectionAlpha = 1.0/2.0;
    algorithmManager = AlgorithmManager();
    layers = Layers();
    //setImage(initialImage());
    //loadFile("C:/Users/corentin/Pictures/test.png");
    loadFile("C:/Users/corentin/Pictures/gfx/Antolach.png");


}

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
        render = Layer(rows, cols, CV_8UC3, new uchar[size], step);
    }
}

void ImageManager::resetLayers() {
    for (Layers::iterator it = layers.begin() ; it != layers.end(); ++it) {
        delete(*it);
    }
    layers.clear();
    layers.push_back(new Layer(mainMatrix));
}

Layer* ImageManager::mainClone() {
    int size = mainMatrix.total() * mainMatrix.elemSize();
    uchar data[size];
    std::memcpy(data, mainMatrix.data, size);
    Layer* l = new Layer(
                mainMatrix.rows,
                mainMatrix.cols,
                CV_8UC3,
                data,
                mainMatrix.step
                );
    return l;
}

void ImageManager::setImage(Layer mat) {

    mainMatrix = mat;
    //std::cout << mainMatrix << std::endl;
    mainImage = QImage(
                mat.data,
                mat.cols,
                mat.rows,
                static_cast<int>(mat.step),
                QImage::Format_RGB888
                );
    mainImage = mainImage.rgbSwapped();
    render = mainMatrix.clone();
    /*uchar* ptr = mainImage.bits();
        for(int i=0; i<27; ++i) {
            std::cout << i << " " << (int)(*(ptr+i)) << std::endl;
        }*/

    qDebug() << "--- initializing layers";
    resetLayers();
    qDebug() << "[V] initializing layers";

}

void ImageManager::setImage(QImage image) {

    qDebug() << "--- new image";
    mainImage = image.convertToFormat(QImage::Format_RGB888);
    qDebug() << "[V] new image";


    /*uchar* ptr = image.bits();
    for(int i=0; i<27; ++i) {
        std::cout << i << " " << (int)(*(ptr+i)) << std::endl;
    }
    ptr = mainImage.bits();
    for(int i=0; i<27; ++i) {
        std::cout << i << " " << (int)(*(ptr+i)) << std::endl;
    }*/

    qDebug() << "--- updating matrix";
    updateMatrixes();
    qDebug() << "[V] updating matrix";


    qDebug() << "--- copying image data into matrix";
    int size = mainMatrix.total() * mainMatrix.elemSize();
    std::memcpy(
                mainMatrix.data,
                mainImage.bits(),
                size
                );
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

QImage ImageManager::getImage() {
    return mainImage;
}

void ImageManager::blend() {
    float beta = 1.0 - selectionAlpha;

    qDebug() << "--- --- cloning matrix";
    //render = mainClone();
    qDebug() << "--- [V] cloning matrix";

    qDebug() << "--- --- layers weighting";
    cv::addWeighted(mainMatrix, selectionAlpha, *layers[0], beta, 0.0, render);
    qDebug() << "--- [V] layers weighting";
}

void ImageManager::applyText(QObject* parameters) {
    qDebug() << "--- matrix updating";
    //fooFill(layers[0]);
    qDebug() << "[V] matrix updating";
    algorithmManager.applyText(&mainMatrix, layers[0], parameters);

    /*std::cout << mainMatrix << std::endl;
    std::cout << *layers[0] << std::endl;
    std::cout << render << std::endl;*/

    qDebug() << "--- layers blending";
    blend();
    qDebug() << "[V] layers blending";


    qDebug() << "--- copying matrix data into image";
    int size = render.total() * render.elemSize();
    std::memcpy(mainImage.bits(), render.data, size);
    qDebug() << "[V] copying matrix data into image";

    /*std::copy(
                std::begin(mainImage.bits()),
                std::end(),
                std::begin()
                );*/

    //mainImage = matToImage(l);
    //std::cout << mainMatrix << std::endl;

    qDebug() << "--- image update";
    imageUpdate();
    qDebug() << "[V] image update";
}

void ImageManager::applyRefine(QObject* parameters) {
    algorithmManager.applyRefine(&mainMatrix, layers[0], parameters);
    qDebug() << "--- layers blending";
    blend();
    qDebug() << "[V] layers blending";
    qDebug() << "--- copying matrix data into image";
    int size = render.total() * render.elemSize();
    std::memcpy(mainImage.bits(), render.data, size);
    qDebug() << "[V] copying matrix data into image";
    qDebug() << "--- image update";
    imageUpdate();
    qDebug() << "[V] image update";
}

void ImageManager::applyLine(QObject* parameters) {
    algorithmManager.applyLine(&mainMatrix, layers[0], parameters);
    qDebug() << "--- layers blending";
    blend();
    qDebug() << "[V] layers blending";
    qDebug() << "--- copying matrix data into image";
    int size = render.total() * render.elemSize();
    std::memcpy(mainImage.bits(), render.data, size);
    qDebug() << "[V] copying matrix data into image";
    qDebug() << "--- image update";
    imageUpdate();
    qDebug() << "[V] image update";
}

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

void blendold() {

    //cout << b << endl;

    //cout << mainMatrix << endl;
    //cout << layers[0] << endl;
    /*int bC = b.channels();
    for(Layer &l : layers) {
        int lC = l.channels();
        for(unsigned y=0; y<l.rows; ++y) {
            for(unsigned x=0; x<l.cols; ++x) {
                int bI = bC*base.cols*y+x;
                int lI = lC*l.cols*y+x;

                RGBA pixel = l.at<RGBA>(y, x);
                if(l.data[lI+3]&255) { //not transparent
                    for(unsigned i = 0; i<4; ++i) {
                        b.data[bI+i] = (int)(
                                (float)b.data[bI+i] * alpha +
                                (float)l.data[lI+i] * beta
                                );
                    }
                }

                if(pixel[0]&0xFF) {
                    layer.at<RGB>(y, x)
                            = layer.at<RGB>(y, x) * 0.5
                            + pixel
                }
            }
        }
    }*/

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




bool ImageManager::loadFile(const QString &fileName)
{
    /*QImageReader reader(fileName);
    reader.setAutoTransform(true);

    const QImage newImage = reader.read();

    if (newImage.isNull()) {
        qDebug() << "fail "+ fileName;
        return false;
    }*/

    Layer mat = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);

    //mainMatrix = mat;

    qDebug() << "setting "+ fileName;

    setImage(mat);

    qDebug() << "update to "+ fileName;

    //QApplication::activeWindow()->setWindowFilePath(fileName);

    qDebug() << "active "+ fileName;

    imageUpdate();

    return true;
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

