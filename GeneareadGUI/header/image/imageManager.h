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

#include <header/io/projectReader.h>
#include <header/io/projectWriter.h>
#include <header/algorithm/algorithmManager.h>
#include <header/tool/drawingTool.h>


typedef cv::Vec3b RGB;
typedef cv::Vec4b RGBA;
typedef cv::Rect Line;

typedef std::function<void(uchar* in, uchar* inout, uchar* layerIn, int i, float alpha, float beta)> LayerBlender;
typedef std::function<void(Layer*, Layer*)> PreviewCreator;
typedef std::function<void(uchar* mat, int x, int y, cv::Vec3b& vec)> PixelPainter;

typedef std::vector<Layer*> Layers;
typedef std::vector<QColor> Colors;
typedef std::vector<QImage*> Previews;
typedef std::vector<DrawingTool*> DrawingTools;
typedef std::vector<PreviewCreator> PreviewCreators;
typedef std::vector<LayerBlender> LayerBlenders;
typedef std::vector<Line> Lines;
typedef struct {
    int top;
    int bottom;
    int left;
    int right;
    int layerID;
} OOB;


class ImageManager : public QObject
{
    Q_OBJECT

public:
    ImageManager(QQmlApplicationEngine* engine);
    /**
     * @brief applyText
     * Applies a text algorithm according to given parameters.
     * The paramter must contain a "textAlgoName" property that defines the name of the text algorithm.
     * @param parameters the requested paramters
     */
    Q_INVOKABLE void applyText(QObject* parameters);

    /**
     * @brief applyLine
     * Applies a line algorithm according to given parameters.
     * The paramter must contain a "lineAlgoName" property that defines the name of the line algorithm.
     * @param parameters the requested paramters
     */
    Q_INVOKABLE void applyLine(QObject* parameters);

    /**
     * @brief applyRefine
     * Applies a refine algorithm according to given parameters.
     * The paramter must contain a "refineAlgoName" property that defines the name of the refine algorithm.
     * @param parameters the requested paramters
     */
    Q_INVOKABLE void applyRefine(QObject* parameters);

    /**
     * @brief loadFile
     * Loads a file from a QString file name.
     * @param parameters the file name
     */
    Q_INVOKABLE bool loadFile(const QString& filename);

    /**
     * @brief toolPressed
     * Applies a drawing tool effect at given coordinates on an appropriate layer.
     * The layer chosen depends on the toolName.
     * @param x the x mouse location on the layer
     * @param y the x mouse location on the layer
     * @param toolName the toolName. From this toolName, a QML parameter object is looked up, giving the color and other parameters to be used
     * @param isRightButton whether the tool is used with a right mouse button click
     */
    Q_INVOKABLE void toolPressed(int x, int y, QString toolName, bool isRightButton);

    /**
     * @brief toolDragged
     * Applies a drawing tool effect between given coordinates on an appropriate layer.
     * The layer chosen depends on the toolName.
     * @param xs the previous x mouse location on the layer
     * @param ys the previous y mouse location on the layer
     * @param xe the current x mouse location on the layer
     * @param ye the current y mouse location on the layer
     * @param toolName the toolName. From this toolName, a QML parameter object is looked up, giving the color and other parameters to be used
     * @param isRightButton whether the tool is used with a right mouse button click
     */
    Q_INVOKABLE void toolDragged(int xs, int ys, int xe, int ye, QString toolName, bool isRightButton);

    /**
     * @brief toolReleased
     * Applies a drawing tool effect at given coordinates on an appropriate layer.
     * The layer chosen depends on the toolName.
     * @param xs the x mouse location on the layer where the mouse was pressed
     * @param ys the y mouse location on the layer where the mouse was pressed
     * @param xe the x mouse location on the layer where the mouse was released
     * @param ye the y mouse location on the layer where the mouse was released
     * @param toolName the toolName. From this toolName, a QML parameter object is looked up, giving the color and other parameters to be used
     * @param isRightButton whether the tool is used with a right mouse button click
     */
    Q_INVOKABLE void toolReleased(int xs, int ys, int xe, int ye, QString toolName, bool isRightButton);


    /**
     * @brief isolateLines
     * Isolate selected lines according to the different layers.
     */
    Q_INVOKABLE void isolateLines();

    /**
     * @brief resetLayers
     * Clears all layers above the opaque bases
     */
    Q_INVOKABLE void resetLayers();

    /**
     * @brief showIsolatedLines
     * Sets the main image shown as separated lines
     */
    Q_INVOKABLE void showIsolatedLines();

    /**
     * @brief showSelectionLayers
     * Sets the main image shown as translucent layers
     */
    Q_INVOKABLE void showSelectionLayers();

    /**
     * @brief toggleHiddenPixels
     * @return true if the hidden pixels are displayed invisible.
     */
    Q_INVOKABLE bool toggleHiddenPixels();

    /**
     * @brief getMainX
     * @return the x position of the main Image on the workspace.
     */
    Q_INVOKABLE int getMainX();

    /**
     * @brief getMainY
     * @return the y position of the main image on the workspace.
     */
    Q_INVOKABLE int getMainY();

    /**
     * @brief getMainWidth
     * @return the width of the main image on the workspace. Zoom included.
     */
    Q_INVOKABLE int getMainWidth();

    /**
     * @brief getMainHeight
     * @return the height of the main image on the workspace. Zoom included.
     */
    Q_INVOKABLE int getMainHeight();

    /**
     * @brief getMaxMainX
     * @return the max x position of the main image on the workspace. Zoom included.
     */
    Q_INVOKABLE int getMaxMainX();

    /**
     * @brief getMaxMainY
     * @return the max y position of the main image on the workspace. Zoom included.
     */
    Q_INVOKABLE int getMaxMainY();

    /**
     * @brief moveMainImage
     * Moves the main image around the workspace
     * @param x the normalized [0.0 -> 1.0] new x position of the mainImage. 0.0 means far left, 1.0 means far right.
     * @param y the normalized [0.0 -> 1.0] new y position of the mainImage. 0.0 means top, 1.0 means bottom.
     */
    Q_INVOKABLE void moveMainImage(float x, float y);

    /**
     * @brief moveMainImage
     * Moves the image by a given distance.
     * @param dx the x distance.
     * @param dy the y distance.
     */
    Q_INVOKABLE void moveMainImage(int dx, int dy);

    /**
     * @brief getPreviewX
     * @return the x position of the previews in the thumbnails.
     */
    Q_INVOKABLE int getPreviewX();

    /**
     * @brief getPreviewY
     * @return the y position of the previews in the thumbnails.
     */
    Q_INVOKABLE int getPreviewY();

    /**
     * @brief getPreviewWidth
     * @return the width of the previews in the thumbnails. Zoom included.
     */
    Q_INVOKABLE int getPreviewWidth();

    /**
     * @brief getPreviewHeight
     * @return the height of the previews in the thumbnails. Zoom included.
     */
    Q_INVOKABLE int getPreviewHeight();

    /**
     * @brief getMaxPreviewX
     * @return the max x position of the the previews in the thumbnails. Zoom included.
     */
    Q_INVOKABLE int getMaxPreviewX();

    /**
     * @brief getMaxPreviewY
     * @return the max x position of the the previews in the thumbnails. Zoom included.
     */
    Q_INVOKABLE int getMaxPreviewY();

    /**
     * @brief movePreviews
     * Moves the zone of the main image focused by the previews.
     * @param x the normalized [0.0 -> 1.0] new x focus of the previews. 0.0 means far left, 1.0 means far right.
     * @param y the normalized [0.0 -> 1.0] new y focus of the previews. 0.0 means top, 1.0 means bottom.
     */
    Q_INVOKABLE void movePreviews(float x, float y);

    /**
     * @brief movePreviews
     * Moves the zone of the main image focused by the previews by a given distance.
     * @param dx the x distance.
     * @param dy the y distance.
     */
    Q_INVOKABLE void movePreviews(int dx, int dy);

    /**
     * @brief shiftPreviewsRight
     * Moves the displayed previews to the right. If no more preview exists, loops back around the previews indefinitly.
     */
    Q_INVOKABLE void shiftPreviewsRight();

    /**
     * @brief shiftPreviewsLeft
     * Moves the displayed previews to the left. If no more preview exists, loops back around the previews indefinitly.
     */
    Q_INVOKABLE void shiftPreviewsLeft();

    /**
     * @brief getSelectedPreviewID
     * @return the id of the actual selected preview. The far left preview is 0.
     */
    Q_INVOKABLE int getSelectedPreviewID();

    /**
     * @brief getLayerAlpha
     * @return the alpha used for blending layers.
     */
    Q_INVOKABLE float getLayerAlpha();

    /**
     * @brief getMainRenderWidth
     * @return the width used by the main image render. Zoom not included.
     */
    Q_INVOKABLE int getMainRenderWidth();

    /**
     * @brief getMainRenderHeight
     * @return the height used by the main image render. Zoom not included.
     */
    Q_INVOKABLE int getMainRenderHeight();

    /**
     * @brief getImageZoom
     * @return the actual float zoom value.
     */
    Q_INVOKABLE float getImageZoom();

    /**
     * @brief getMaxZoomIndex
     * @return the maximum times the image can be zoomed in or out.
     */
    Q_INVOKABLE int getMaxZoomIndex();

    /**
     * @brief getZoomMultiplier
     * @return the multipling value applied to the zoom when zoomed in or out.
     */
    Q_INVOKABLE float getZoomMultiplier();

    /**
     * @brief getZoomIndex
     * @return the zoom index value. 0 means 1:1 scale. negative means the display is smaller, positive means the display is bigger.
     */
    Q_INVOKABLE int getZoomIndex();

    /**
     * @brief zoomIn
     * Increases zoom index and updates view.
     */
    Q_INVOKABLE void zoomIn();

    /**
     * @brief zoomOut
     * Decreases zoom index and updates view.
     */
    Q_INVOKABLE void zoomOut();

    /**
     * @brief resetZoom
     * Sets zoom index to 0.
     */
    Q_INVOKABLE void resetZoom();

    /**
     * @brief hasPreviewSelected
     * @deprecated
     * @return
     */
    Q_INVOKABLE bool hasPreviewSelected();

    /**
     * @brief isPreviewSelected
     * @param previewID the preview ID.
     * @return true if the selected preview ID is <code>previewID</code>. False otherwise.
     */
    Q_INVOKABLE bool isPreviewSelected(int previewID);

    /**
     * @brief selectPreview
     * Selects a preview. Sends a signal to QML to display the selection.
     * @param previewID the preview ID.
     */
    Q_INVOKABLE void selectPreview(int previewID);

    /**
     * @brief resetPreviewSelection
     * Resets the selected preview and preview focus.
     * Effectively selects the default preview.
     */
    Q_INVOKABLE void resetPreviewSelection();

    /**
     * @brief applyPreview
     * Refreshes the preview at a given index.
     * @param id the index
     */
    Q_INVOKABLE void applyPreview(int id);

    /**
     * @brief getSelectedAlgorithmID
     * @return the algorithm index corresponding to the selected preview. 0 means no algorithm.
     */
    Q_INVOKABLE int getSelectedAlgorithmID();

    /**
     * @brief init
     * Called once to load the default images and data
     */
    Q_INVOKABLE void init();

    /**
     * @brief resetBaseMatrix
     * Sets the back matrix to an empty black image.
     */
    void resetBaseMatrix();

    /**
     * @brief basePreviews
     * Sets the backMatrix as a base for all previews.
     * Reallocates memory to match the backMatrix size if needed.
     */
    void basePreviews();

    /**
     * @brief resetPreviews
     * Rebases and reapply previews.
     */
    void resetPreviews();

    /**
     * @brief resets
     * Resets the backMatrix and all the previews.
     */
    void reset();

    /**
     * @brief read
     * Reads imageManager data using a project reader.
     * Creates all the layers.
     * (saving algorithm ID was causing crashes so it was removed halfway in)
     * (has trouble loading big image files. A fix seems to be required in the way ProjectReader handles int value ?)
     * @param reader the reader
     */
    void read(ProjectReader* reader);

    /**
     * @brief read
     * Write imageManager data using a project writer.
     * Saves all the layers.
     * @todo add more parameters to save.
     * (saving algorithm ID was causing crashes so it was removed halfway in)
     * @param writer the writer
     */
    void write(ProjectWriter* writer);

    /**
     * @brief saveFile
     * @deprecated
     * @param fileName
     * @return
     */
    bool saveFile(const QString &fileName);

    /**
     * @brief isShowingSelectionLayers
     * @return true if the main image shows the translucent layers. False otherwise.
     */
    bool isShowingSelectionLayers();

    /**
     * @brief isShowingIsolatedLines
     * @return true if the main image shows isolated black and white lines. False otherwise.
     * @return
     */
    bool isShowingIsolatedLines();

    /**
     * @brief getDrawingTool
     * @param name the tool name.
     * @return a pointer to a given drawing tool named <code>name</code>.
     */
    DrawingTool* getDrawingTool(QString name);

    /**
     * @brief createLine
     * @param line
     * @param lineObject
     * @param parent
     * @todo actually create lines.
     */
    void createLine(Line& line, QObject* lineObject, QObject* parent);

    /**
     * @brief getImage
     * @return the main matrix's QML image
     */
    QImage getImage();

    /**
     * @brief getPreview
     * @param id the preview id.
     * @return the preview's QML image of given id.
     */
    QImage getPreview(int id);

    /**
     * @brief getDefaultImageWidth
     * @deprecated unused
     * @return
     */
    int getDefaultImageWidth();

    /**
     * @brief getDefaultImageHeight
     * @deprecated unused
     * @return
     */
    int getDefaultImageHeight();

    /**
     * @brief setImage
     * @deprecated unused
     * @param image
     */
    void setImage(QImage image);

    /**
     * @brief setImage
     * @deprecated unused
     * @param mat
     */
    void setImage(Layer mat);

    /**
     * @brief getMainMatrix
     * @deprecated unused
     * @return
     */
    Layer getMainMatrix();

    /**
     * @brief onImageUpdate
     * @deprecated unused
     */
    void onImageUpdate();


public slots:

signals:
    void imageUpdate();
    void imageSizeUpdate();
    void imageMoved();
    void previewsUpdate();
    void previewUpdate();
    void previewSelection();
    void previewDeselection();
    void previewSizeChanged();
    void previewSelectionReset();

protected:
    QQmlApplicationEngine* engine;
    //QQmlContext root;
    //QObject textAlgorithManager;

    AlgorithmManager algorithmManager;
    DrawingTools drawingTools;
    Layers layers;
    Layers previewLayers;
    Colors colors;
    Lines lines;
    ProjectReader projectReader;
    ProjectWriter projectWriter;

    LayerBlenders layerBlenders;
    int selectedLayerBlenderID;

    Previews previews;
    PreviewCreators previewCreators;
    int previewFocusID;
    int selectedPreviewID;
    bool previewSelected;
    int nbPreviewsDisplayed;
    int nbPreviewsMax;

    float previewX;
    float previewY;
    int previewWidth;
    int previewHeight;
    Layer* previewReference;

    float mainX;
    float mainY;
    int mainXint;
    int mainYint;
    int mainWidth;
    int mainHeight;
    QImage mainImage;
    Layer backMatrix;
    Layer textMatrix;
    Layer lineMatrix;
    Layer mainMatrix;
    Layer hiddenLayer;
    Layer mask;
    Layer render;

    int lineSpacing;
    cv::Vec3b lineSpaceColor;
    cv::Vec3b lineBackColor;

    int hideDeletedPixels;

    float zoom;
    int zoomIndex;
    float zoomMultiplier;

    double selectionAlpha;
    bool showingSelectionLayer;
    bool imageReady;
    bool useLayersAsMask;


private slots:
    /**
     * @brief initLayerBlenders
     * Sets all the layer blenders once and for all.
     */
    void initLayerBlenders();

    /**
     * @brief print
     * @deprecated unused
     */
    void print();

    /**
     * @brief copy
     * @deprecated unused
     */
    void copy();

    /**
     * @brief paste
     * @deprecated unused
     */
    void paste();

    /**
     * @brief rebasePreviews
     * Updates the base reference used by previews and their sizes.
     * @param reference the new reference used for copying pixels from
     * @param width the new preview width.
     * @param height the new preview height.
     */
    void rebasePreviews(Layer* reference, int width, int height);

    /**
     * @brief rebasePreviews
     * Refreshes the previews using their references.
     */
    void rebasePreviews();

    /**
     * @brief rebasePreview
     * Refreshes one preview using its reference.
     * @param id the preview ID.
     */
    void rebasePreview(int id);

    /**
     * @brief applyPreviews
     * applies algorithms to each preview.
     */
    void applyPreviews();

    /**
     * @brief applyPreview
     * applies an algorithm linked to a preview.
     * @param id the preview ID.
     * @param RGBMatrix the reference RGB matrix.
     * @param mask the pixel mask used by the algorithm.
     */
    void applyPreview(int id, Layer* RGBMatrix, Layer* mask);

    /**
     * @brief updateZoom
     * updates the zoom value according to this zoom index.
     * Send a signal to QML to update the scale of the QImage.
     */
    void updateZoom();

    /**
     * @brief newLayer
     * creates a new translucent layer and ads it to the layer list.
     * @return the newly created layer.
     */
    Layer* newLayer();

    /**
     * @brief selectLine
     * Selects a line object.
     * @todo add support for line objects to make this method useful.
     * @param lineID the line object ID.
     */
    void selectLine(int lineID);

    /**
     * @brief addPreview
     * @deprecated unused
     * @param textAlgoName
     */
    void addPreview(QString textAlgoName);

    /**
     * @brief getLayer
     * @param color the color to find.
     * @return the first layer using given color in its display.
     */
    Layer* getLayer(QColor color);

    /**
     * @brief getMaskLayer
     * @return the layer that should be used as a mask.
     * If a mask exists, returns it. Return the first transluscent layer otherwise.
     */
    Layer* getMaskLayer();

    /**
     * @brief updateBackMatrix
     * Sets new data to the backMatrix.
     * Resets all the layers and update some renders accordingly.
     * @param layer
     */
    void updateBackMatrix(Layer layer);

    /**
     * @brief setMainRenderData
     * Sets the layer used as reference for the render.
     * @param RGBMatrix the address of the layer.
     */
    void setMainRenderData(Layer& RGBMatrix);

    /**
     * @brief RGBALayer
     * @deprecated unused
     * @return a new RGBA matrix the same size as mainMatrix
     */
    Layer* RGBALayer();

    /**
     * @brief RGBLayer
     * @deprecated unused
     * @return a new RGB matrix the same size as mainMatrix
     */
    Layer* RGBLayer();

    /**
     * @brief mainClone
     * @deprecated unused
     * @return a clone of mainMatrix
     */
    Layer* mainClone();

    LayerBlender* getLayerBlender();
    LayerBlender* getHiddenLayerBlender();

    /**
     * @brief blend
     * Blends all the layers.
     * @param in the input base layer.
     * @param out the output render.
     */
    void blend(Layer* in, Layer* out);

    /**
     * @brief blendAndUpdate
     * Blends all the layers and update the view.
     * @param in the input base layer.
     * @param out the output render.
     */
    void blendAndUpdate(Layer* in, Layer* out);

    void resetDisplayInside(Layer* in, Layer* out, Layer* mask);

    /**
     * @brief initialImage
     * @deprecated unused
     * @return
     */
    QImage initialImage();

    /**
     * @brief imageToMat
     * @deprecated unused
     * @return
     */
    void imageToMat(QImage image, Layer* matrix);

    /**
     * @brief matToImage
     * @deprecated unused
     * @return
     */
    void matToImage(Layer matrix, QImage* image);

    /**
     * @brief updateMatrixes
     * @deprecated unused
     * @return
     */
    void updateMatrixes();
};

#endif // IMAGEMANAGER_H
