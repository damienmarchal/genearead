#ifndef NIBLACKDERIVEDALGORITHM_H
#define NIBLACKDERIVEDALGORITHM_H

#include "textAlgorithm.h"

/**
 * @brief The NiblackDerivedAlgorithm class is an abstract implementation of Niblack's segmentation algorithm.
 * Subclasses implementing this have to provide a factor calculation in the "threshold" method.
 */
class NiblackDerivedAlgorithm : public TextAlgorithm {

public:
    NiblackDerivedAlgorithm();
    double calcLocalStats(Layer* in, Layer* out_m, Layer* out_s, Layer* mask);

    virtual void apply(Layer* in, Layer* out, Layer* mask);
    /**
     * @brief threshold
     * computes a threshold for given factors
     * @param m
     * @param s
     * @param min_I
     * @param max_I
     * @param max_s
     * @return
     */
    virtual double threshold(double m, double s, double min_I, double max_I, double max_s) = 0;

protected:
    int winx;
    int winy;

};

#endif // NIBLACKDERIVEDALGORITHM_H
