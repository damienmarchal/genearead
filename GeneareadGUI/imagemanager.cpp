#include <QQmlEngine>
#include <QtWidgets>
#include <QQmlComponent>
#include <QFileDialog>
#include <QDebug>

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent)
    : QObject(parent)
{
    count = 0;

    setImage(initialImage());


}

QImage ImageManager::initialImage() {
    QImage image = QImage(200, 200, QImage::Format_RGB32);
    QPainter paint;
    paint.begin(&image);
    paint.fillRect(QRectF(0, 0, this->image.width(), this->image.height()), QColor(0, 0, 0));
    paint.setPen(QColor(255, 255, 255));
    paint.setBrush(QColor(255, 255, 255));
    paint.drawText(QPointF(10, 10), "NO IMAGE");
    return image;
}

void ImageManager::resetLayers() {
    layers = Layers();
    layers.push_back(RGBLayer());
}

static void fooFill(Layer l) {

    std::srand(std::time(0)); // use current time as seed for random generator

    //RNG rng();
    //rng.fill(matrix2xN, cv::RNG::NORMAL, mean, sigma);
    int wasTrue = false;
    for(unsigned y=0; y<l.rows; ++y) {
        for(unsigned x=0; x<l.cols; ++x) {
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

Layer ImageManager::RGBALayer() {
    return Layer(mainMatrix.rows, mainMatrix.cols, CV_8UC4);
}

Layer ImageManager::RGBLayer() {
    return Layer(mainMatrix.rows, mainMatrix.cols, CV_8UC3);
}

Layer ImageManager::mainClone() {
    return mainMatrix.clone();
}


Layer ImageManager::blend() {
    float alpha = 0.5f;
    float beta = 1.0f - alpha;
    qDebug() << "--- --- cloning matrix";
    Layer b = RGBLayer();
    qDebug() << "--- [V] cloning matrix";
    qDebug() << "--- --- layers weighting";
    addWeighted(mainMatrix, alpha, layers[0], beta, 0.0, b);
    qDebug() << "--- [V] layers weighting";
    //cout << b << endl;




    //cout << mainMatrix << endl;
    //cout << layers[0] << endl;
    return b;
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

void ImageManager::setImage(QImage image) {
    qDebug() << "--- new image";
    //delete this->image;
    this->image = image.convertToFormat(QImage::Format_RGB888);
    qDebug() << "[V] new image";
    //delete mainMatrix;
    mainMatrix = imageToMat(&(this->image));
    resetLayers();
}

QImage ImageManager::getImage() {
    return this->image;
}

cv::Mat ImageManager::imageToMat(QImage* img)
{
    qDebug() << "--- image to matrix";
    cv::Mat mat = cv::Mat(
                img->height(),
                img->width(),
                CV_8UC3,
                img->bits(),
                img->bytesPerLine()
                );
    qDebug() << "[V] image to matrix";
    return mat;
}

QImage ImageManager::matToImage(cv::Mat* mat)
{
    qDebug() << "--- matrix to image";
    QImage image = QImage(
                mat->data,
                mat->cols,
                mat->rows,
                static_cast<int>(mat->step),
                QImage::Format_RGB888
                );
    qDebug() << "[V] matrix to image";
    return image;
    //return image.rgbSwapped();
}

struct Operator {
    void apply(cv::Point3_<unsigned char> &pixel, int * position) {
        pixel.x = 255;
    }
};

void ImageManager::apply(QString algorithm) {
    qDebug() << "--- matrix updating";
    fooFill(layers[0]);
    qDebug() << "[V] matrix updating";
    qDebug() << "--- layers blending";
    Layer l = blend();
    qDebug() << "[V] layers blending";
    image = matToImage(&l);
    imageUpdate();


    //mainMatrix.forEach<Pixel>(Operator());
    //mainMatrix.forEach<cv::Point3_<unsigned char>>(Operator::apply);


    /*for(Pixel &p : cv::Mat_<Pixel>(mainMatrix)) {
        p.x = 255;
    }*/
}

void ImageManager::onImageUpdate() {
    qDebug() << "[V] image update";
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
    QImageReader reader(fileName);
    reader.setAutoTransform(true);

    const QImage newImage = reader.read();

    if (newImage.isNull()) {
        qDebug() << "fail "+ fileName;
        return false;
    }

    qDebug() << "setting "+ fileName;

    setImage(newImage);

    qDebug() << "update to "+ fileName;

    //QApplication::activeWindow()->setWindowFilePath(fileName);

    qDebug() << "active "+ fileName;

    imageUpdate();

    return true;
}

bool ImageManager::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
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
    QGuiApplication::clipboard()->setImage(image);
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

