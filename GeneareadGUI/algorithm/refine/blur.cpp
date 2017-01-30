#include "blur.h"

#include <opencv2/imgproc/imgproc.hpp>

Blur::Blur()
    : ksize(3)
{

}

QString Blur::getName() {
    return "blur";
}

void Blur::setParameters(QObject* parameters) {

}

void Blur::apply(Layer* in, Layer* out, Layer* mask) {
    cv::medianBlur(*in, *out, ksize);
}
