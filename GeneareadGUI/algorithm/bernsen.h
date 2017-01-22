#ifndef BERNSEN_H
#define BERNSEN_H

#include <algorithm/algorithm.h>

class Bernsen : public Algorithm {

public:
    Bernsen();
    virtual QString getName();
    virtual void apply(Layer* in, Layer* out, Layer* mask);
    virtual void setParameters(QObject* parameters);

protected:
    int k;

};

#endif // BERNSEN_H
