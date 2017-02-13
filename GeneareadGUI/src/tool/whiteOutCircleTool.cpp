#include <header/tool/whiteOutCircleTool.h>

WhiteOutCircleTool::WhiteOutCircleTool() {

}

QString WhiteOutCircleTool::getName() {
    return "whiteOut";
}

cv::Scalar WhiteOutCircleTool::getActualColor(cv::Scalar color, bool isRightButton) {
    qDebug() << isRightButton;
    return isRightButton ? cv::Scalar(0, 0, 0) : cv::Scalar(255, 255, 255);
}

bool WhiteOutCircleTool::usesHiddenLayer() {
    return true;
}
