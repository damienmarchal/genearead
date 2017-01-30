#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QObject>
#include <QColor>
#include <QDebug>

#include <namedinstance.h>

class DrawingTool {

public:
    virtual ~DrawingTool() {}

    virtual QString getName() = 0;
    virtual void draw(Layer* layer, int x, int y, cv::Scalar color, QObject* parameters) = 0;

};

#endif // DRAWINGTOOL_H
