#ifndef REFINEALGORITHM_H
#define REFINEALGORITHM_H

#include <QObject>
#include <QDebug>

#include "../algorithm.h"

class RefineAlgorithm {

public:
    virtual ~RefineAlgorithm() {}

    virtual QString getName() = 0;
    virtual void apply(Layer* in, Layer* out, Layer* mask) = 0;
    virtual void setParameters(QObject* parameters) = 0;

};

#endif // REFINEALGORITHM_H
