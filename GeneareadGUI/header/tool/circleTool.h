#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "drawingTool.h"

/**
 * @brief The CircleTool class draws circles of given radius and color whenever the mouse is pressed or dragged.
 */
class CircleTool : public DrawingTool {

public:
    CircleTool();
    virtual QString getName();
    virtual void mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject* parameters);
    virtual void mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters);
    virtual void mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters);
    virtual cv::Scalar getActualColor(cv::Scalar color, bool isRightButton);
    virtual bool usesHiddenLayer();

    virtual bool requiresNewLayerOnPressed(cv::Scalar color);
    virtual bool requiresNewLayerOnDragged(cv::Scalar color);
    virtual bool requiresNewLayerOnReleased(cv::Scalar color);
};

#endif // CIRCLETOOL_H
