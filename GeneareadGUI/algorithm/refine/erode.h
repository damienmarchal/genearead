#ifndef ERODE_H
#define ERODE_H

#include "refineAlgorithm.h"

class Erode : public RefineAlgorithm {

public:
    Erode();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    Layer kernel;
    cv::Point anchor;
    int iterations;
    int borderType;
    cv::Scalar borderValue;
};

#endif // ERODE_H
