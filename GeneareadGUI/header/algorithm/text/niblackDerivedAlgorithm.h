#ifndef NIBLACKDERIVEDALGORITHM_H
#define NIBLACKDERIVEDALGORITHM_H

#include "textAlgorithm.h"

class NiblackDerivedAlgorithm : public TextAlgorithm {

public:
    NiblackDerivedAlgorithm();
    double calcLocalStats(Layer* in, Layer* out_m, Layer* out_s, Layer* mask);

    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual double threshold(double m, double s, double min_I, double max_I, double max_s) = 0;

protected:
    int winx;
    int winy;

};

#endif // NIBLACKDERIVEDALGORITHM_H
