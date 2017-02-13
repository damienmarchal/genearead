#include <iterator>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

#include <QQmlEngine>
#include <QtWidgets>
#include <QQmlComponent>
#include <QFileDialog>
#include <QDebug>
#include <QColor>

#include <header/image/imageManager.h>

#include <header/tool/noTool.h>
#include <header/tool/selectTool.h>
#include <header/tool/circleTool.h>
#include <header/tool/rectangleTool.h>
#include <header/tool/eraserCircleTool.h>
#include <header/tool/whiteOutCircleTool.h>

ImageManager::ImageManager(QQmlApplicationEngine* engine)
    : QObject(0)
{
    this->engine = engine;

    algorithmManager = AlgorithmManager();
    layers = Layers();
    colors = Colors();
    lines = Lines();
    layerBlenders = LayerBlenders();

    zoomMultiplier = 1.1f;
    resetZoom();

    previewX = 0.5f;
    previewY = 0.5f;
    useLayersAsMask = false;

    lineSpacing = 30;
    lineSpaceColor = cv::Vec3b(0xFF, 0xFF, 0xFF);
    lineBackColor = cv::Vec3b(0xFF, 0xFF, 0xFF);

    nbPreviewsDisplayed = 3;
    nbPreviewsMax = 10;
    previewFocusID = nbPreviewsMax-(nbPreviewsDisplayed/2);
    selectionAlpha = 1.0/2.0;

    previews = Previews();
    previewLayers = Layers();
    previewCreators = PreviewCreators();

    previews.resize(nbPreviewsMax);
    previewLayers.resize(nbPreviewsMax);
    previewCreators.resize(nbPreviewsMax);

    drawingTools = DrawingTools();
    drawingTools.push_back(new NoTool());
    drawingTools.push_back(new SelectTool());
    drawingTools.push_back(new CircleTool());
    drawingTools.push_back(new RectangleTool());
    drawingTools.push_back(new EraserCircleTool());
    drawingTools.push_back(new WhiteOutCircleTool());

    initLayerBlenders();
    selectedLayerBlenderID = 2;
    hideDeletedPixels=0b11111111;

    resetBaseMatrix();
    basePreviews();

}

void ImageManager::resetBaseMatrix() {
    updateBackMatrix(Layer::zeros(150, 100, CV_8UC3));
    imageUpdate();
}

void ImageManager::basePreviews() {
    int width = previewWidth ? previewWidth : 100;
    int height = previewHeight ? previewHeight : 150;
    rebasePreviews(&backMatrix, width, height);
}

void ImageManager::resetPreviews() {
    basePreviews();
    applyPreviews();
    resetPreviewSelection();
    previewsUpdate();
}

void ImageManager::reset() {
    resetBaseMatrix();
    resetPreviews();
}

void ImageManager::init() {
    applyPreviews();
    resetPreviewSelection();
    previewsUpdate();
    moveMainImage(0.5f, 0.5f);
}

void ImageManager::initLayerBlenders() {

    //pixels characters blend
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float, float) {
        if(!in[i] && !in[i+1] && !in[i+2] && (layerIn[i] || layerIn[i+1] || layerIn[i+2])) { //non transparent pixel
            inout[i  ] = hideDeletedPixels;
            inout[i+1] = hideDeletedPixels;
            inout[i+2] = hideDeletedPixels;
        }
    });

    //gray layer blend
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float alpha, float beta) {
        if(layerIn[i] || layerIn[i+1] || layerIn[i+2]) { //non transparent pixel
            inout[i  ] = std::round(inout[i  ]*beta + layerIn[i  ]*alpha);
            inout[i+1] = std::round(inout[i+1]*beta + layerIn[i+1]*alpha);
            inout[i+2] = std::round(inout[i+2]*beta + layerIn[i+2]*alpha);
        } else {//transparent pixel
            //do nothing
        }
    });

    //white layer blend
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float alpha, float beta) {
        if(layerIn[i] || layerIn[i+1] || layerIn[i+2]) { //non transparent pixel
            inout[i  ] = std::round(inout[i  ]*beta + layerIn[i  ]*alpha);
            inout[i+1] = std::round(inout[i+1]*beta + layerIn[i+1]*alpha);
            inout[i+2] = std::round(inout[i+2]*beta + layerIn[i+2]*alpha);
        } else {//transparent pixel
            //do nothing
        }
    });

    //alpha blend
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float alpha, float beta) {
        if(layerIn[i] || layerIn[i+1] || layerIn[i+2]) { //non transparent pixel
            inout[i  ] = std::round(inout[i  ]*beta + layerIn[i  ]*alpha);
            inout[i+1] = std::round(inout[i+1]*beta + layerIn[i+1]*alpha);
            inout[i+2] = std::round(inout[i+2]*beta + layerIn[i+2]*alpha);
        } else {//transparent pixel
            //do nothing
        }
    });

    //pixels characters primary color blend
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float, float) {
        inout[i  ] |= layerIn[i  ];
        inout[i+1] |= layerIn[i+1];
        inout[i+2] |= layerIn[i+2];
    });

    //pixels characters primary color blend + transluscent background
    layerBlenders.push_back([&](uchar* in, uchar* inout, uchar* layerIn, int i, float alpha, float beta) {
        if(in[i] || in[i+1] || in[i+2]) { //back is not black
            if(layerIn[i] || layerIn[i+1] || layerIn[i+2]) { //mask covers it
                if(layerIn[i  ])
                    inout[i  ] = std::max(inout[i  ], (uchar)std::round(layerIn[i  ]*alpha));
                if (layerIn[i+1])
                    inout[i+1] = std::max(inout[i+1], (uchar)std::round(layerIn[i+1]*alpha));
                if (layerIn[i+2])
                    inout[i+2] = std::max(inout[i+2], (uchar)std::round(layerIn[i+2]*alpha));
            }
        } else { //back is black
            inout[i  ] |= layerIn[i  ];
            inout[i+1] |= layerIn[i+1];
            inout[i+2] |= layerIn[i+2];
        }
    });

}

bool ImageManager::toggleHiddenPixels() {
    hideDeletedPixels = (hideDeletedPixels==0b11111111)
            ? 0b10111111
            : 0b11111111;
    blendAndUpdate(&mainMatrix, &render);
    return hideDeletedPixels==0b01111111;
}

float ImageManager::getImageZoom() {
    return zoom;
}

float ImageManager::getZoomMultiplier() {
    return zoomMultiplier;
}

void ImageManager::updateZoom() {
    int z = getZoomIndex();
    zoom = 1.0f;
    if(z) {
        float mul = getZoomMultiplier();
        if(z<0) {
            mul = 1.0f/mul;
            z = -z;
        }
        for(int i=0; i<z; ++i)
            zoom *= mul;
    }
    imageSizeUpdate();
}

int ImageManager::getZoomIndex() {
    return zoomIndex;
}

int ImageManager::getMaxZoomIndex() {
    return 10;
}

void ImageManager::resetZoom() {
    zoomIndex = 0;
    updateZoom();
}

void ImageManager::zoomIn() {
    zoomIndex = std::min(zoomIndex+1, getMaxZoomIndex());
    updateZoom();
}

void ImageManager::zoomOut() {
    zoomIndex = std::max(zoomIndex-1, -getMaxZoomIndex());
    updateZoom();
}

void ImageManager::read(ProjectReader* reader) {
    updateBackMatrix(*(reader->readMat()));

    int nbLayers = reader->readInt();
    layers.resize(nbLayers);
    for(int i=0; i<nbLayers; ++i) {
        layers[i] = reader->readMat();
    }
    rebasePreviews(&backMatrix, 100, 150);
    applyPreviews();
    blendAndUpdate(&mainMatrix, &render);
}

void ImageManager::write(ProjectWriter* writer) {
    writer->writeMat(&backMatrix);
    int nbLayers = layers.size();
    writer->writeInt(nbLayers);
    for(int i=0; i<nbLayers; ++i) {
        writer->writeMat(layers[i]);
    }
}

void ImageManager::isolateLines() {
    int chan = mainMatrix.channels();
    int height = mainMatrix.rows;
    int width = mainMatrix.cols;
    int chanWidth = width*chan;
    int size = width*height;

    std::vector<Layer> ls = std::vector<Layer>();
    std::vector<OOB> oobs = std::vector<OOB>();
    Layer layerCopy = Layer(height, width, CV_8UC1);
    Layer connected = Layer(height, width, CV_16U);
    int i, j, k;
    int nbLayers = layers.size();
    uint16_t* cp;

    int nb = 0;
    int nb_l;
    uint16_t bottom, top;

    for(j=0; j<nbLayers; ++j) {
        cv::cvtColor(*layers[j], layerCopy, CV_RGB2GRAY);
        nb_l = cv::connectedComponents(layerCopy, connected, 4, CV_16U) - 1;
        oobs.resize(nb + nb_l);
        for(i=nb; i<nb+nb_l; ++i) {
            oobs[i].top = -1;
            oobs[i].bottom = -1;
            oobs[i].left = -1;
            oobs[i].right = -1;
            oobs[i].layerID = -1;
        }

        cp = connected.ptr<uint16_t>();
        k = size-1;
        for(i=0; i<size; ++i) {
            top = cp[i];
            if(top) {
                std::cout << i << " " << cp[i] << std::endl;
                top = nb+top-1;
                if(oobs[top].top==-1) {
                    oobs[top].top = i/width;
                    oobs[top].layerID = j;
                }
            }
            bottom = cp[k];
            if(bottom) {
                bottom = nb+bottom-1;
                if(oobs[bottom].bottom==-1) {
                    oobs[bottom].bottom = k/width;
                    oobs[bottom].layerID = j;
                }
            }
            --k;
        }
        nb += nb_l;
    }

    //ordering oobs
    std::sort(oobs.begin(), oobs.end(), [&](const OOB& a,const OOB& b){
        return a.top < b.top;
    });

    int rows = 0;
    for(i=0; i<nb; ++i) {
        rows += oobs[i].bottom - oobs[i].top + 1;
        rows += lineSpacing;
    }


    lineMatrix = Layer(Layer::zeros(rows, width, CV_8UC3));
    uchar* lp = lineMatrix.ptr();
    cv::Vec3b vec;

    for(i=0; i<rows*mainMatrix.cols*chan; i+=chan) {
        lp[i  ] = lineSpaceColor[0];
        lp[i+1] = lineSpaceColor[1];
        lp[i+2] = lineSpaceColor[2];

    }

    int x, y, rx, ry;

    rx = 0;
    ry = 0;
    Layer* lll;
    for(i=0; i<nb; ++i) {
        lll = layers[oobs[i].layerID];
        for(y=oobs[i].top; y<=oobs[i].bottom; ++y) {
            for(x=0; x<lineMatrix.cols; ++x) {
                vec = lll->at<cv::Vec3b>(y, x);
                lineMatrix.at<cv::Vec3b>(ry+y-oobs[i].top, rx+x) =
                        (vec[0] || vec[1] || vec[2])
                        ? mainMatrix.at<cv::Vec3b>(y, x)
                        : lineBackColor;
            }
        }
        ry += lineSpacing + oobs[i].bottom - oobs[i].top + 1;
    }

}

bool ImageManager::isShowingIsolatedLines() {
    return !showingSelectionLayer;
}

bool ImageManager::isShowingSelectionLayers() {
    return showingSelectionLayer;
}

void ImageManager::showIsolatedLines() {
    if(isShowingIsolatedLines())
        return;
    isolateLines();
    setMainRenderData(lineMatrix);
    showingSelectionLayer = false;
}

void ImageManager::showSelectionLayers() {
    if(isShowingSelectionLayers())
        return;
    setMainRenderData(render);
    showingSelectionLayer = true;
}

int ImageManager::getMainRenderWidth() {return mainImage.width();}
int ImageManager::getMainRenderHeight() {return mainImage.height();}

void ImageManager::setMainRenderData(Layer& RGBMatrix) {
    mainImage = QImage(
                RGBMatrix.data,
                RGBMatrix.cols,
                RGBMatrix.rows,
                static_cast<int>(RGBMatrix.step),
                QImage::Format_RGB888);
    imageSizeUpdate();
    imageUpdate();
}

void ImageManager::shiftPreviewsLeft() {
    previewFocusID = (previewFocusID+1)%nbPreviewsMax;
    selectedPreviewID = (selectedPreviewID+nbPreviewsMax-1)%nbPreviewsMax;
    previewsUpdate();
}

void ImageManager::shiftPreviewsRight() {
    previewFocusID = (previewFocusID+nbPreviewsMax-1)%nbPreviewsMax;
    selectedPreviewID = (selectedPreviewID+1)%nbPreviewsMax;
    previewsUpdate();
}

int ImageManager::getSelectedAlgorithmID() {
    return (previewFocusID + selectedPreviewID) % nbPreviewsMax;
}

bool ImageManager::hasPreviewSelected() {
    return selectedPreviewID;
}

bool ImageManager::isPreviewSelected(int previewID) {
    return selectedPreviewID==previewID;
}

void ImageManager::resetPreviewSelection() {
    int id = nbPreviewsDisplayed/2;
    previewFocusID = nbPreviewsMax-id;
    selectPreview(id);
}

void ImageManager::selectPreview(int previewID) {
    previewDeselection();
    selectedPreviewID = previewID;
    backMatrix.copyTo(mainMatrix);
    applyPreview(getSelectedAlgorithmID(), &mainMatrix, getMaskLayer());
    blendAndUpdate(&mainMatrix, &render);
    previewSelection();
    previewSelected = getSelectedAlgorithmID();
}

float ImageManager::getLayerAlpha() {return selectionAlpha;}
int ImageManager::getPreviewWidth() {return previewWidth;}
int ImageManager::getPreviewHeight() {return previewHeight;}
int ImageManager::getSelectedPreviewID() {return selectedPreviewID;}
int ImageManager::getMaxPreviewX() {return previewReference->cols-previewWidth;}
int ImageManager::getMaxPreviewY() {return previewReference->rows-previewHeight;}
int ImageManager::getPreviewX() {return std::round(getMaxPreviewX()*previewX);}
int ImageManager::getPreviewY() {return std::round(getMaxPreviewY()*previewY);}

int ImageManager::getMainWidth() {return mainWidth;}
int ImageManager::getMainHeight() {return mainHeight;}
int ImageManager::getMaxMainX() {
    QObject* canvas = engine->rootObjects().first()->findChild<QObject*>("mainCanvas");
    int width = canvas->property("width").toInt();
    return width - backMatrix.cols*zoom;
}
int ImageManager::getMaxMainY() {
    QObject* canvas = engine->rootObjects().first()->findChild<QObject*>("mainCanvas");
    int height = canvas->property("height").toInt();
    return height - backMatrix.rows*zoom;
}
int ImageManager::getMainX() {return std::round(getMaxMainX()*mainX);}
int ImageManager::getMainY() {return std::round(getMaxMainY()*mainY);}

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

void ImageManager::createLine(Line& line, QObject* lineObject, QObject* parent) {
    int rx = parent->property("width").toInt();
    int ry = parent->property("height").toInt();
    int x = 10;
    int y = (line.y + line.height) / 2 * zoom;
    lineObject->setProperty("x", x);
    lineObject->setProperty("y", y);
    qDebug() << x << y;
    lines.push_back(line);
}

void ImageManager::selectLine(int lineID) {

}

Layer* ImageManager::newLayer() {
    Layer* layer = new Layer(Layer::zeros(backMatrix.rows, backMatrix.cols, CV_8UC3));
    layers.push_back(layer);
    qDebug() << "new layer (" << layer->size << ")";
    return layer;
}


DrawingTool* ImageManager::getDrawingTool(QString name) {
    DrawingTool* t;
    for(unsigned i=0; i<drawingTools.size(); ++i) {
        t = drawingTools[i];
        if(t->getName() == name)
            return t;
    }
    return drawingTools[0];
}

cv::Scalar colorToscalar(QColor color) {
    int r,g,b;
    color.getRgb(&r, &g, &b);
    return cv::Scalar(r,g,b);
}

QColor scalarToColor(cv::Scalar color) {
    return QColor(color[0],color[1],color[2]);
}

void ImageManager::toolPressed(int x, int y, QString toolName, bool isRightButton) {
    qDebug() << toolName;
    QObject* parameters = engine->rootObjects().first()->findChild<QObject*>(toolName+"Parameters");
    qDebug() << parameters;
    QColor color = parameters->property("color").value<QColor>();
    DrawingTool* tool = getDrawingTool(toolName);
    cv::Scalar scalar = tool->getActualColor(colorToscalar(color), isRightButton);

    Layer* layer = tool->usesHiddenLayer()
            ? &hiddenLayer
            : tool->requiresNewLayerOnPressed(scalar)
              ? newLayer()
              : getLayer(color);


    if(tool == NULL)
        return;

    tool->mousePressed(this, layer, x, y, colorToscalar(color), parameters);
    blendAndUpdate(&mainMatrix, &render);
}


void ImageManager::toolDragged(int xs, int ys, int xe, int ye, QString toolName, bool isRightButton) {
    QObject* parameters = engine->rootObjects().first()->findChild<QObject*>(toolName+"Parameters");
    QColor color = parameters->property("color").value<QColor>();
    DrawingTool* tool = getDrawingTool(toolName);
    cv::Scalar scalar = tool->getActualColor(colorToscalar(color), isRightButton);

    Layer* layer = tool->usesHiddenLayer()
            ? &hiddenLayer
            : tool->requiresNewLayerOnPressed(scalar)
              ? newLayer()
              : getLayer(color);

    if(tool == NULL)
        return;

    tool->mouseDragged(this, layer, xs, ys, xe, ye, colorToscalar(color), parameters);
    blendAndUpdate(&mainMatrix, &render);
}

void ImageManager::toolReleased(int xs, int ys, int xe, int ye, QString toolName, bool isRightButton) {
    QObject* parameters = engine->rootObjects().first()->findChild<QObject*>(toolName+"Parameters");
    QColor color = parameters->property("color").value<QColor>();
    DrawingTool* tool = getDrawingTool(toolName);
    cv::Scalar scalar = tool->getActualColor(colorToscalar(color), isRightButton);

    Layer* layer = tool->usesHiddenLayer()
            ? &hiddenLayer
            : tool->requiresNewLayerOnPressed(scalar)
              ? newLayer()
              : getLayer(color);

    if(tool == NULL)
        return;

    tool->mouseReleased(this, layer, xs, ys, xe, ye, colorToscalar(color), parameters);
    blendAndUpdate(&mainMatrix, &render);
}

Layer* ImageManager::mainClone() {
    return new Layer(mainMatrix.clone());
}

void ImageManager::updateBackMatrix(Layer layer) {
    backMatrix = layer;
    mainWidth = layer.cols;
    mainHeight = layer.rows;
    mainMatrix = backMatrix.clone();
    hiddenLayer = Layer(Layer::zeros(backMatrix.rows, backMatrix.cols, CV_8UC3));
    render = backMatrix.clone();
    mainImage = QImage(
                render.data,
                render.cols,
                render.rows,
                static_cast<int>(render.step),
                QImage::Format_RGB888);
    resetLayers();
    moveMainImage(mainX, mainY);
    updateZoom();
}

bool ImageManager::loadFile(const QString& fileName) {
    Layer l = cv::imread(fileName.toStdString(), cv::IMREAD_COLOR);
    backMatrix = Layer(l.rows, l.cols, CV_8UC3);
    cv::cvtColor(l, backMatrix, cv::COLOR_RGBA2BGR);
    updateBackMatrix(backMatrix);
    resetPreviews();
    imageUpdate();
    return true;
}

void ImageManager::resetLayers() {
    for(size_t i=0; i<layers.size(); ++i) {
        delete(layers[i]);
    }
    layers.clear();
    colors.clear();
}

Layer* ImageManager::getLayer(QColor color) {
    for(size_t i=0; i<colors.size(); ++i) {
        if(color == colors[i])
            return layers[i];
    }
    colors.push_back(color);
    return newLayer();
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

void ImageManager::rebasePreview(int id) {
    Layer roi = (*previewReference)(cv::Rect(getPreviewX(), getPreviewY(), previewWidth, previewHeight));
    roi.copyTo(*previewLayers[id]);
}

void ImageManager::movePreviews(float x, float y) {
    x = std::min(std::max(0.0f, x), 1.0f);
    y = std::min(std::max(0.0f, y), 1.0f);
    if(previewX!=x || previewY!=y) {
        previewX = x;
        previewY = y;
        rebasePreviews();
        applyPreviews();
    }
}

void ImageManager::movePreviews(int dx, int dy) {
    movePreviews(
                (float)(getPreviewX() + dx)/getMaxPreviewX(),
                (float)(getPreviewY() + dy)/getMaxPreviewY()
                );
}

void ImageManager::moveMainImage(float x, float y) {
    x = std::min(std::max(0.0f, x), 1.0f);
    y = std::min(std::max(0.0f, y), 1.0f);
    if(mainX!=x || mainY!=y) {
        mainX = x;
        mainY = y;
    }
    imageMoved();
}

void ImageManager::moveMainImage(int dx, int dy) {
    qDebug() << "moved main        " << dx << dy;
    qDebug() << "moved main (float)" << (float)(getMainX() + dx) << (float)(getMainY() + dy);
    moveMainImage(
                (float)(getMainX() + dx)/getMaxMainX(),
                (float)(getMainY() + dy)/getMaxMainY()
                );
}

void ImageManager::applyPreviews() {
    const int max = nbPreviewsMax;
    for(int i=1; i<max; ++i) {
        applyPreview(i, previewLayers[i], getMaskLayer());
    }
    previewsUpdate();
}

void ImageManager::applyPreview(int id, Layer* RGBMatrix, Layer* mask) {
    QObject* parameters =
            engine->rootObjects().first()
            ->findChild<QObject*>("algoColumn")
            ->children().at(id+1)
            ->children().first();
    for(QObject* param : parameters->children()) {
        algorithmManager.applyText(RGBMatrix, mask, param);
        algorithmManager.applyLine(RGBMatrix, mask, param);
        algorithmManager.applyRefine(RGBMatrix, mask, param);
    }
}

void ImageManager::applyPreview(int id) {
    rebasePreview(id);
    applyPreview(id, previewLayers[id], getMaskLayer());
    previewUpdate();

    backMatrix.copyTo(mainMatrix);
    applyPreview(getSelectedAlgorithmID(), &mainMatrix, getMaskLayer());
    blendAndUpdate(&mainMatrix, &render);
}

LayerBlender* ImageManager::getLayerBlender() {
    return &layerBlenders[selectedLayerBlenderID];
}

LayerBlender* ImageManager::getHiddenLayerBlender() {
    return &layerBlenders[0];
}

void ImageManager::blend(Layer* in, Layer* out) {

    in->copyTo(*out);

    int chan = in->channels();
    int height = in->rows;
    int width = in->cols * chan;
    int size = width * height;
    uchar* p = in->ptr();
    uchar* r = out->ptr();
    uchar* l;
    float a = selectionAlpha;
    float b = 1.0f-a;
    int i;
    LayerBlender* blender = getLayerBlender();
    LayerBlender* hiddenBlender = getHiddenLayerBlender();


    l = hiddenLayer.ptr();
    for(i=0; i<size; i+=chan) {
        (*hiddenBlender)(p, r, l, i, a, b);
    }
    for(Layer* layer : layers) {
        l = layer->ptr();
        for(i=0; i<size; i+=chan) {
            (*blender)(p, r, l, i, a, b);
        }
    }
}

void ImageManager::blendAndUpdate(Layer* in, Layer* out) {
    blend(in, out);
    imageUpdate();
}

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
    if(!useLayersAsMask || layers.empty()) {
        if(&mask==NULL || cols != mask.cols || rows != mask.rows) {
            mask = Layer::ones(rows, cols, CV_8UC3);
        }
        return &mask;
    }
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

    QObject* parameters = engine->rootObjects().first()->findChild<QObject*>(textAlgoName);
    Layer* mask = getMaskLayer();

    algorithmManager.applyText(layer, mask, parameters);
    QImage* image = new QImage(
                layer->data,
                layer->cols,
                layer->rows,
                static_cast<int>(layer->step),
                QImage::Format_RGB888);
    previews.push_back(image);
}

QImage ImageManager::getPreview(int id) {
    return *previews[(previewFocusID+id)%nbPreviewsMax];
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
    }
}


void ImageManager::setImage(Layer mat) {

    mainMatrix = mat;

    resetLayers();

}

void ImageManager::setImage(QImage image) {

    mainImage = image.convertToFormat(QImage::Format_RGB888);


    updateMatrixes();

;
    int size = mainMatrix.total() * mainMatrix.elemSize();
    uchar* src = mainImage.bits();
    uchar* dest = mainMatrix.data;
    std::memcpy(dest, src, size);

    std::cout << size << std::endl;
    std::cout << mainMatrix.total() << std::endl;
    std::cout << mainMatrix.elemSize() << std::endl;
    std::cout << mainMatrix.step << std::endl;
    std::cout << mainMatrix << std::endl;

    resetLayers();
}

void ImageManager::imageToMat(QImage, Layer*) {
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

void ImageManager::matToImage(Layer, QImage*) {
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

