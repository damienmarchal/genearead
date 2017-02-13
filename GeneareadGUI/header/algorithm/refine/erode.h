#ifndef ERODE_H
#define ERODE_H

#include "refineAlgorithm.h"

/**
 * @brief The Erode class is a RefineAlgorithm that dilates the non-black pixels of a Layer.
 * After applying this algorithm, every isolated non-black pixel is turned black.
 * This class uses the cv::erode implementation.
 * See documentation for cv::erode for informations about any class fields of this class.
 */
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
