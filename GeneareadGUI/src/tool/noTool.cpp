#include <header/algorithm/algorithm.h>
#include <header/tool/noTool.h>
#include <header/image/imageManager.h>

NoTool::NoTool() {}

QString NoTool::getName() {return "noTool";}

void NoTool::mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject* parameters) {}
void NoTool::mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {
    imageManager->moveMainImage(xe-xs, ye-ys);
}
void NoTool::mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {}

cv::Scalar NoTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return color;
}

bool NoTool::usesHiddenLayer() {
    return false;
}

bool NoTool::requiresNewLayerOnPressed(cv::Scalar color) {return false;}
bool NoTool::requiresNewLayerOnDragged(cv::Scalar color) {return false;}
bool NoTool::requiresNewLayerOnReleased(cv::Scalar color) {return false;}
