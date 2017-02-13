#ifndef WHITEINCIRCLETOOL_H
#define WHITEINCIRCLETOOL_H

#include "circleTool.h"

/**
 * @brief The WhiteInCircleTool class draws black (effectively transparent) circles of given radius whenever the mouse is pressed or dragged.
 * This class can only draw on the hidden layer.
 */
class WhiteInCircleTool : public CircleTool {

public:
    WhiteInCircleTool();
    virtual QString getName();
    virtual cv::Scalar getActualColor(cv::Scalar color, bool isRightButton);
    virtual bool usesHiddenLayer();
};

#endif // WHITEINCIRCLETOOL_H
