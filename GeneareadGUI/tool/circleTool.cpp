#include "circleTool.h"

#include <opencv2/imgproc.hpp>

CircleTool::CircleTool() {

}

QString CircleTool::getName() {
    return "pinceau"; //gomme rectangle
}

void CircleTool::draw(Layer* layer, int x, int y, cv::Scalar color, QObject *parameters) {
    int radius;

    QVariant v;
    if(!(v=parameters->property("radius")).isNull())
        radius = v.toInt();

    qDebug() << "drawing circle";
    cv::circle(*layer, cv::Point2f(x+0.5, y+0.5), radius, color, -1);
}
