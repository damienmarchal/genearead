#include <header/algorithm/algorithm.h>
#include <header/tool/selectTool.h>
#include <header/image/imageManager.h>

SelectTool::SelectTool() {}

QString SelectTool::getName() {return "select";}

void SelectTool::mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject* parameters) {}

void SelectTool::mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {
    imageManager->moveMainImage(xe-xs, ye-ys);
}

void SelectTool::mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {}

cv::Scalar SelectTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return color;
}

bool SelectTool::usesHiddenLayer() {
    return false;
}

bool SelectTool::requiresNewLayerOnPressed(cv::Scalar color) {return false;}
bool SelectTool::requiresNewLayerOnDragged(cv::Scalar color) {return false;}
bool SelectTool::requiresNewLayerOnReleased(cv::Scalar color) {return false;}
