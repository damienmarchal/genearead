#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "textAlgorithm.h"

#include <opencv2/imgproc/imgproc.hpp>

class Threshold : public TextAlgorithm {

public:
    Threshold();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int T;
    cv::ThresholdTypes thresholdType;

};

#endif // THRESHOLD_H
