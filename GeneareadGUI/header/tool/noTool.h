#ifndef NOTOOL_H
#define NOTOOL_H

#include "drawingTool.h"

/**
 * @brief The NoTool class should be used when no tool is selected. Can still be used to move the image around the workspace.
 */
class NoTool : public DrawingTool {

public:
    NoTool();
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

#endif // NOTOOL_H
