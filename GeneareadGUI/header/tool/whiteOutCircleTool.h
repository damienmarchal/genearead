#ifndef WHITEOUTCIRCLETOOL_H
#define WHITEOUTCIRCLETOOL_H

#include "circleTool.h"

/**
 * @brief The WhiteOutCircleTool class draws lightgray (effectively white) circles of given radius whenever the mouse is pressed or dragged.
 * This class can only draw on the hidden layer.
 */
class WhiteOutCircleTool : public CircleTool {

public:
    WhiteOutCircleTool();
    virtual QString getName();
    virtual cv::Scalar getActualColor(cv::Scalar color, bool isRightButton);
    virtual bool usesHiddenLayer();
};

#endif // WHITEOUTCIRCLETOOL_H
