#ifndef DILATE_H
#define DILATE_H

#include "refineAlgorithm.h"

/**
 * @brief The Dilate class is a RefineAlgorithm that dilates the non-black pixels of a Layer.
 * After applying this algorithm, every originally non-black pixel is surrounded by more non-black pixels.
 * This class uses the cv::dilate implementation.
 * See documentation for cv::dilate for informations about any class fields of this class.
 */
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
