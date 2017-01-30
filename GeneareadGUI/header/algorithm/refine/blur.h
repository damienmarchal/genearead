#ifndef BLUR_H
#define BLUR_H

#include "refineAlgorithm.h"

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
