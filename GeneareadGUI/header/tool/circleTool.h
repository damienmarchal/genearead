#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "drawingTool.h"

class CircleTool : public DrawingTool {

public:
    CircleTool();
    virtual QString getName();
    virtual void draw(Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters);

};

#endif // CIRCLETOOL_H
