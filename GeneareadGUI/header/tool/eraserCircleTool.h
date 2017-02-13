#ifndef ERASERCIRCLETOOL_H
#define ERASERCIRCLETOOL_H

#include "circleTool.h"

/**
 * @brief The EraserCircleTool class draws black (effectively transparent) circles of given radius whenever the mouse is pressed or dragged.
 */
class EraserCircleTool : public CircleTool {

public:
    EraserCircleTool();
    virtual QString getName();
    virtual cv::Scalar getActualColor(cv::Scalar color, bool isRightButton);
};

#endif // ERASERCIRCLETOOL_H
