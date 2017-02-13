#include <header/tool/whiteInCircleTool.h>

WhiteInCircleTool::WhiteInCircleTool() {

}

QString WhiteInCircleTool::getName() {
    return "whiteIn";
}

cv::Scalar WhiteInCircleTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return cv::Scalar(0, 0, 0);
}

bool WhiteInCircleTool::usesHiddenLayer() {
    return true;
}
