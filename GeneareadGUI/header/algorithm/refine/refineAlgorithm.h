#ifndef REFINEALGORITHM_H
#define REFINEALGORITHM_H

#include <QObject>
#include <QDebug>

#include "../algorithm.h"

/**
 * @brief The RefineAlgorithm class is the interface for refining algorithms
 */
class RefineAlgorithm {

public:
    virtual ~RefineAlgorithm() {}

    /**
     * @brief getName
     * @return the name of this algorithm
     */
    virtual QString getName() = 0;

    /**
     * @brief apply
     * Applies this algorithm to a gray CV_8UC1 Layer according to a mask.
     * If mask at (x, y) is not 0, the algorithm is applied at pixel (x, y).
     * Otherwise, it is not.
     *
     * @param in the input CV_8UC1 layer
     * @param out the output CV_8UC1 layer
     * @param mask the mask
     */
    virtual void apply(Layer* in, Layer* out, Layer* mask) = 0;

    /**
     * @brief setParameters
     * Sets the parameters of this algorithm.
     * A parameter not present or invalid shoudl be ignored.
     * @param parameters the parameter object. Its properties can be retrieved using :
     *        parameters->properties(PARAMETER_NAME)
     * where PARAMETER_NAME is the QString name of a parameter.
     */
    virtual void setParameters(QObject* parameters) = 0;

};

#endif // REFINEALGORITHM_H
