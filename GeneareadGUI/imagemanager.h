#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <vector>
#include <functional>

#include <opencv2/core.hpp>

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <algorithm/algorithmManager.h>
#include <tool/drawingTool.h>


typedef cv::Vec3b RGB;
typedef cv::Vec4b RGBA;
typedef std::vector<Layer*> Layers;
typedef std::vector<QColor> Colors;
typedef std::vector<QImage*> Previews;
typedef std::vector<DrawingTool*> DrawingTools;
//typedef void (*PreviewCreator)(Layer*, Layer*);
typedef std::function<void(Layer*, Layer*)> PreviewCreator;

typedef std::vector<PreviewCreator> PreviewCreators;

class ImageManager : public QObject
{
    Q_OBJECT

public:
    ImageManager(QQmlApplicationEngine* engine);
    Q_INVOKABLE void add(QObject* image, QString source);
    Q_INVOKABLE void open();
    Q_INVOKABLE void applyText(QObject* parameters);
    Q_INVOKABLE void applyLine(QObject* parameters);
    Q_INVOKABLE void applyRefine(QObject* parameters);
    //Q_INVOKABLE void resetDisplay();
    Q_INVOKABLE bool loadFile(const QString &);
    Q_INVOKABLE void mouseDown(int x, int y, QString toolName, QColor color, QObject* sizeParameters);
    Q_INVOKABLE void isolateLines();
    Q_INVOKABLE void resetLayers();
    Q_INVOKABLE void shiftPreviewsRight();
    Q_INVOKABLE void shiftPreviewsLeft();
    Q_INVOKABLE int getSelectedPreviewID();
    Q_INVOKABLE int getPreviewX();
    Q_INVOKABLE int getPreviewY();
    Q_INVOKABLE int getPreviewWidth();
    Q_INVOKABLE int getPreviewHeight();
    Q_INVOKABLE int getMaxPreviewX();
    Q_INVOKABLE int getMaxPreviewY();
    Q_INVOKABLE void movePreviews(float x, float y);

    bool saveFile(const QString &fileName);
    //QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    int getDefaultImageWidth();
    int getDefaultImageHeight();
    void setImage(QImage image);
    void setImage(Layer mat);
    QImage getImage();
    Layer getMainMatrix();
    void onImageUpdate();
    DrawingTool* getDrawingTool(QString name);

    QImage getPreview(int id);

public slots:

signals:
    void imageUpdate();
    void previewsUpdate();
    void previewUpdate();
    void previewSizeChanged();

protected:
    QQmlApplicationEngine* engine;
    //QQmlContext root;
    //QObject textAlgorithManager;

    AlgorithmManager algorithmManager;
    DrawingTools drawingTools;
    Layers layers;
    Colors colors;

    Previews previews;
    Layers previewLayers;
    PreviewCreators previewCreators;
    int selectedPreviewID;

    int nbPreviewsDisplayed;
    int nbPreviewsMax;
    float previewX;
    float previewY;
    int previewWidth;
    int previewHeight;
    Layer* previewReference;

    QImage mainImage;
    Layer backMatrix;
    Layer textMatrix;
    Layer lineMatrix;
    Layer mainMatrix;
    Layer mask;
    Layer render;

    double selectionAlpha;
    bool imageReady;


private slots:
    void initPreviewCreators();
    void saveAs();
    void print();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void rebasePreviews();
    void rebasePreviews(Layer* reference, int width, int height);
    void applyPreviews();


    void addPreview(QString textAlgoName);
    Layer* getLayer(QColor color);
    Layer* getMaskLayer();
    void updateBackMatrix(Layer layer);

    Layer* RGBALayer();
    Layer* RGBLayer();
    Layer* mainClone();
    void blend(Layer* in, Layer* out);
    void blendAndUpdate(Layer* in, Layer* out);
    void resetDisplayInside(Layer* in, Layer* out, Layer* mask);
    QImage initialImage();

    void imageToMat(QImage image, Layer* matrix);
    void matToImage(Layer matrix, QImage* image);

    void updateMatrixes();
};

#endif // IMAGEMANAGER_H
