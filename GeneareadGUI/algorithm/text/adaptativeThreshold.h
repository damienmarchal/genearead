#ifndef ADAPTIVETHRESHOLD_H
#define ADAPTIVETHRESHOLD_H

#include "textAlgorithm.h"

#include <opencv2/imgproc/imgproc.hpp>

class AdaptiveThreshold : public TextAlgorithm {

public:
    AdaptiveThreshold();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int w;
    int C;
    cv::ThresholdTypes thresholdType;
    cv::AdaptiveThresholdTypes adaptiveMethod;

};

#endif // ADAPTIVETHRESHOLD_H
