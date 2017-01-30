#include <header/algorithm/refine/erode.h>

#include <opencv2/imgproc/imgproc.hpp>

Erode::Erode()
    : kernel(Layer())
    , anchor(cv::Point(-1, -1))
    , iterations(1)
    , borderType(cv::BORDER_CONSTANT)
    , borderValue(cv::morphologyDefaultBorderValue())
{

}

QString Erode::getName() {
    return "erode";
}

void Erode::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("iterations")).isNull())
        iterations = v.toInt();

    if(!(v = parameters->property("borderType")).isNull())
        borderType = v.toInt();

    if(!(v = parameters->property("anchorX")).isNull())
        anchor.x = v.toInt();

    if(!(v = parameters->property("anchorY")).isNull())
        anchor.y = v.toInt();

}

void Erode::apply(Layer* in, Layer* out, Layer* mask) {
    cv::erode(*in, *out, kernel, anchor, iterations, borderType, borderValue);
}
