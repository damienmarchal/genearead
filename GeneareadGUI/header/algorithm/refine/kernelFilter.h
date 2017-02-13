#ifndef KERNELFILTER_H
#define KERNELFILTER_H

#include "refineAlgorithm.h"

/**
 * @brief The KernelFilter class is a RefineAlgorithm that acts as a kernel filter on a Layer.
 * This class uses the cv::filter2D implementation.
 * See documentation for cv::filter2D for informations about any class fields of this class.
 */
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
