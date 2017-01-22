#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QDebug>

#include <opencv2/core.hpp>

typedef unsigned char uc;
typedef cv::Point3_<uc> Pixel;
typedef cv::Mat Layer;

class Algorithm {

public:
    virtual ~Algorithm() {}
    virtual QString getName() = 0;
    virtual void apply(Layer* in, Layer* out, Layer* mask) = 0;
    virtual void setParameters(QObject* parameters) = 0;

};

#endif // ALGORITHM_H
