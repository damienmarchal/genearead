#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "drawingTool.h"

/**
 * @brief The RectangleTool class should be used for selections in the image.
 * Is intented to interact with line objects.
 * Can currently be used to move the image around the workspace.
 */
class SelectTool : public DrawingTool {

public:
    SelectTool();
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

#endif // SELECTTOOL_H
