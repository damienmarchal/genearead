#include <header/tool/eraserCircleTool.h>

EraserCircleTool::EraserCircleTool() {

}

QString EraserCircleTool::getName() {
    return "eraser";
}

cv::Scalar EraserCircleTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return cv::Scalar(0, 0, 0);
}
