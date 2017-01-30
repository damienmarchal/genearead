#ifndef TEXTALGORITHM_H
#define TEXTALGORITHM_H

#include <QObject>
#include <QDebug>

#include "../algorithm.h"

class TextAlgorithm {

public:
    virtual ~TextAlgorithm() {}

    virtual QString getName() = 0;
    virtual void apply(Layer* in, Layer* out, Layer* mask) = 0;
    virtual void setParameters(QObject* parameters) = 0;

    void applyMask(Layer* in, Layer* out, Layer* mask);

};

#endif // TEXTALGORITHM_H
