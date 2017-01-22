#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <vector>

#include <opencv2/core.hpp>

#include <QObject>
#include <QImage>
#include <QDebug>

#include <algorithmManager.h>

typedef cv::Vec3b RGB;
typedef cv::Vec4b RGBA;
typedef std::vector<Layer*> Layers;

class ImageManager : public QObject
{
    Q_OBJECT

public:
    explicit ImageManager(QObject *parent = 0);
    Q_INVOKABLE void add(QObject *image, QString source);
    Q_INVOKABLE void open();
    Q_INVOKABLE void apply(QObject* parameters);

    Q_INVOKABLE bool loadFile(const QString &);
    bool saveFile(const QString &fileName);
    //QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    int getDefaultImageWidth();
    int getDefaultImageHeight();
    void setImage(QImage image);
    void setImage(Layer mat);
    QImage getImage();
    Layer getMainMatrix();
    void onImageUpdate();

public slots:

signals:
    void imageUpdate();

protected:
    int count;
    QImage mainImage;
    Layer mainMatrix;
    Layer render;
    Layers layers;
    AlgorithmManager algorithmManager;
    double selectionAlpha;

private slots:
    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void resetLayers();

    Layer* RGBALayer();
    Layer* RGBLayer();
    Layer* mainClone();
    void blend();
    QImage initialImage();

    void imageToMat(QImage image, Layer* matrix);
    void matToImage(Layer matrix, QImage* image);

    void updateMatrixes();
};

#endif // IMAGEMANAGER_H
