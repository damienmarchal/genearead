#ifndef DILATE_H
#define DILATE_H

#include "refineAlgorithm.h"

class Dilate : public RefineAlgorithm {

public:
    Dilate();
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

#endif // DILATE_H
