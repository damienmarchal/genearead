#ifndef BLUR_H
#define BLUR_H

#include "refineAlgorithm.h"

/**
 * @brief The Blur class is a RefineAlgorithm that hads a blur effect on a layer
 * This class uses the cv::medianBlur implementation.
 * See documentation for cv::medianBlur for informations about any class fields of this class.
 */
class Blur : public RefineAlgorithm {

public:
    Blur();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int ksize;
};

#endif // BLUR_H
