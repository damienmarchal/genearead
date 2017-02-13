#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QObject>
#include <QColor>
#include <QDebug>

#include <opencv2/imgproc.hpp>

#include <header/algorithm/algorithm.h>

class ImageManager;

/**
 * @brief The DrawingTool class is an interface for all drawing tools used in the project.
 * Provides methods for when the mouse if pressed, dragged and released above a mouse area.
 * Also provides methods to interact with a calling ImageManger.
 */
class DrawingTool {

public:
    virtual ~DrawingTool() {}

    /**
     * @brief getName
     * @return the name of this tool
     */
    virtual QString getName() = 0;

    /**
     * @brief mousePressed
     * @param imageManager the calling ImageManager
     * @param layer the layer to draw onto. Can be a new one according to requiresNewLayerOnPressed.
     * @param x the x mouse location on the layer
     * @param y the x mouse location on the layer
     * @param color a suggested color.
     * @param parameters other parameters defined by QString keys.
     */
    virtual void mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject* parameters) = 0;

    /**
     * @brief mouseDragged
     * @param imageManager the calling ImageManager
     * @param layer the layer to draw onto. Can be a new one according to requiresNewLayerOnDragged.
     * @param xs the previous x mouse location on the layer
     * @param ys the previous y mouse location on the layer
     * @param xe the current x mouse location on the layer
     * @param ye the current y mouse location on the layer
     * @param color a suggested color.
     * @param parameters other parameters defined by QString keys.
     */
    virtual void mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) = 0;

    /**
     * @brief mouseReleased
     * @param imageManager the calling ImageManager
     * @param layer the layer to draw onto. Can be a new one according to requiresNewLayerOnDragged.
     * @param xs the x mouse location on the layer where the mouse was pressed
     * @param ys the y mouse location on the layer where the mouse was pressed
     * @param xe the x mouse location on the layer where the mouse was released
     * @param ye the y mouse location on the layer where the mouse was released
     * @param color a suggested color.
     * @param parameters other parameters defined by QString keys.
     */
    virtual void mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) = 0;

    /**
     * @brief getActualColor
     * @param color a suggested color.
     * @param isRightButton wheteher the mouse was using the right button.
     * @return the actual color used by the tool. The parametered color and isRightButton flag should be used as suggestions.
     */
    virtual cv::Scalar getActualColor(cv::Scalar color, bool isRightButton) = 0;

    /**
     * @brief usesHiddenLayer
     * @return true if this class should draw on the hidden layer
     * (aka the layer containing pixel to set as background). False otherwise.
     */
    virtual bool usesHiddenLayer() = 0;

    /**
     * @brief requiresNewLayerOnPressed
     * @param color the color used by the tool.
     * @return true if a new layer should be creatd when the mouse is pressed with a given color.
     */
    virtual bool requiresNewLayerOnPressed(cv::Scalar color) = 0;

    /**
     * @brief requiresNewLayerOnDragged
     * @param color the color used by the tool.
     * @return true if a new layer should be creatd when the mouse is dragged with a given color.
     */
    virtual bool requiresNewLayerOnDragged(cv::Scalar color) = 0;

    /**
     * @brief requiresNewLayerOnReleased
     * @param color the color used by the tool.
     * @return true if a new layer should be creatd when the mouse is released with a given color.
     */
    virtual bool requiresNewLayerOnReleased(cv::Scalar color) = 0;

};

#endif // DRAWINGTOOL_H
