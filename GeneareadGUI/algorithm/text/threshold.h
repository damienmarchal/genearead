#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "textAlgorithm.h"

class Threshold : public TextAlgorithm {

public:
    Threshold();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int k;

};

#endif // THRESHOLD_H
