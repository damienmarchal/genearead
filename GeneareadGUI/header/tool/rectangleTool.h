#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "drawingTool.h"

/**
 * @brief The RectangleTool class draws rectangle between the positions the mouse was pressed and released.
 */
class RectangleTool : public DrawingTool {

public:
    RectangleTool();
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

#endif // RECTANGLETOOL_H
