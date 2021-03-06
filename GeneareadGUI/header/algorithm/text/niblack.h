#ifndef NIBLACK_H
#define NIBLACK_H

#include "niblackDerivedAlgorithm.h"

/**
 * @brief The Niblack class is a TextAlgorithm. The default Niblack algorithm implementation.
 */
class Niblack : public NiblackDerivedAlgorithm {

public:
    Niblack();
    virtual QString getName();
    virtual void setParameters(QObject* parameters);
    virtual double threshold(double m, double s, double min_I, double max_I, double max_s);

protected:
    double k;

};

#endif // NIBLACK_H
