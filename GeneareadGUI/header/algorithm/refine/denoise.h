#ifndef DENOISE_H
#define DENOISE_H

#include "refineAlgorithm.h"

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
