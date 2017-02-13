#ifndef DENOISE_H
#define DENOISE_H

#include "refineAlgorithm.h"

/**
 * @brief The Blur class is a RefineAlgorithm that reduces noise on a layer
 * This class uses the cv::fastNlMeansDenoising implementation.
 * See documentation for cv::fastNlMeansDenoising for informations about any class fields of this class.
 */
class Denoise : public RefineAlgorithm {

public:
    Denoise();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    float h;

};

#endif // DENOISE_H
