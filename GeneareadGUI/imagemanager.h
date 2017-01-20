#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QImage>
#include <QDebug>

#include <vector>
#include <algorithm.h>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

typedef Vec3b RGB;
typedef Vec4b RGBA;
typedef Mat Layer;
typedef vector<Mat> Layers;

class ImageManager : public QObject
{
    Q_OBJECT

public:
    explicit ImageManager(QObject *parent = 0);
    Q_INVOKABLE void add(QObject *image, QString source);
    Q_INVOKABLE void open();
    Q_INVOKABLE void apply(QString algorithm);

    Q_INVOKABLE bool loadFile(const QString &);
    bool saveFile(const QString &fileName);
    //QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    int getDefaultImageWidth();
    int getDefaultImageHeight();
    void setImage(QImage image);
    QImage getImage();
    cv::Mat getMainMatrix();
    void onImageUpdate();

public slots:

signals:
    void imageUpdate();

protected:
    int count;
    QImage image;
    cv::Mat mainMatrix;
    Layers layers;

private slots:
    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void resetLayers();

    Layer RGBALayer();
    Layer RGBLayer();
    Layer mainClone();
    Layer blend();
    QImage initialImage();

    cv::Mat imageToMat(QImage* img);
    QImage matToImage(cv::Mat* mat);
};

#endif // IMAGEMANAGER_H
