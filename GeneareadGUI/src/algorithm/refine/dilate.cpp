#include <header/algorithm/refine/dilate.h>

#include <opencv2/imgproc/imgproc.hpp>

Dilate::Dilate()
    : kernel(Layer())
    , anchor(cv::Point(-1, -1))
    , iterations(1) //[1-10]
    , borderType(cv::BORDER_CONSTANT)
    , borderValue(cv::morphologyDefaultBorderValue())
{

}

QString Dilate::getName() {
    return "dilate";
}

void Dilate::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("iterations")).isNull())
        iterations = std::round(v.toFloat()*2.0f)+1;

    if(!(v = parameters->property("borderType")).isNull())
        borderType = v.toInt();

    if(!(v = parameters->property("anchorX")).isNull())
        anchor.x = v.toInt();

    if(!(v = parameters->property("anchorY")).isNull())
        anchor.y = v.toInt();

}

void Dilate::apply(Layer* in, Layer* out, Layer* mask) {
    cv::dilate(*in, *out, kernel, anchor, iterations, borderType, borderValue);
}
