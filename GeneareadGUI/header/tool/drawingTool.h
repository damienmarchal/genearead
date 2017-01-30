#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QObject>
#include <QColor>
#include <QDebug>

class DrawingTool {

public:
    virtual ~DrawingTool() {}

    virtual QString getName() = 0;
    virtual void draw(Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) = 0;

};

#endif // DRAWINGTOOL_H
