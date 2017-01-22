#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <algorithm/algorithm.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class Threshold : public Algorithm {

public:
    Threshold();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int k;

};

#endif // THRESHOLD_H
