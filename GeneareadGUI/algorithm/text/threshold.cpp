#include "threshold.h"

Threshold::Threshold()
    : T(127)
    , thresholdType(cv::THRESH_BINARY)
{

}

QString Threshold::getName() {
    return "threshold";
}

void Threshold::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("T")).isNull()) {
        T = v.toInt();
    }

    if(!(v = parameters->property("inv")).isNull()) {
        thresholdType = v.toBool() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    }

}

void Threshold::apply(Layer* in, Layer* out, Layer* mask) {
    cv::threshold(*in, *out, T, 255, thresholdType);
    applyMask(in, out, mask);
}

