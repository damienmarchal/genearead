#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "drawingTool.h"

class CircleTool : public DrawingTool {

public:
    CircleTool();
    virtual QString getName();
    virtual void draw(Layer* layer, int x, int y, cv::Scalar color, QObject* parameters);

};

#endif // CIRCLETOOL_H
