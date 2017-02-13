#include <header/algorithm/algorithm.h>
#include <header/tool/rectangleTool.h>

#include <header/io/project.h>

Project* PROJECT;

RectangleTool::RectangleTool() {

}

QString RectangleTool::getName() {
    return "rectangle";
}

void RectangleTool::mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject *parameters) {

}

void RectangleTool::mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject *parameters) {

}

void RectangleTool::mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {
    //cv::rectangle(*layer, cv::Rect2i(0, 0, layer->cols, layer->rows), cv::Scalar(0xDF, 0xDF, 0xDF), -1);
    int a;
    if(xs>xe) {
        a = xs;
        xs = xe;
        xe = a;
    }
    if(ys>ye) {
        a = ys;
        ys = ye;
        ye = a;
    }

    cv::Rect line(xs, ys, xe-xs, ye-ys);
    cv::rectangle(*layer, line, color, -1);
    //PROJECT->createLineIndex(line);

}

cv::Scalar RectangleTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return color;
}

bool RectangleTool::usesHiddenLayer() {
    return false;
}

bool RectangleTool::requiresNewLayerOnPressed(cv::Scalar color) {return false;}
bool RectangleTool::requiresNewLayerOnDragged(cv::Scalar color) {return false;}
bool RectangleTool::requiresNewLayerOnReleased(cv::Scalar color) {return true;}
