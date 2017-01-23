#ifndef SAUVOLA_H
#define SAUVOLA_H

#include "niblackDerivedAlgorithm.h"

class Sauvola : public NiblackDerivedAlgorithm {

public:
    Sauvola();
    virtual QString getName();
    virtual void setParameters(QObject* parameters);
    virtual double threshold(double m, double s, double min_I, double max_I, double max_s);

protected:
    double k;
    double R;

};

#endif // SAUVOLA_H
