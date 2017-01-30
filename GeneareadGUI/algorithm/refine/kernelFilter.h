#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "refineAlgorithm.h"

class KernelFilter : public RefineAlgorithm {

public:
    KernelFilter();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int ddepth;
    Layer kernel;
    cv::Point anchor;
    int delta;
    int borderType;


};

#endif // KERNELFILTER_H
