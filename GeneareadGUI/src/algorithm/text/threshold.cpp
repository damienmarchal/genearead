#include <header/algorithm/text/threshold.h>

Threshold::Threshold()
    : t(127)
    , thresholdType(cv::THRESH_BINARY)
{

}

QString Threshold::getName() {
    return "threshold";
}

void Threshold::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("t")).isNull()) {
        t = std::round(v.toFloat()*255);
    }

    if(!(v = parameters->property("inv")).isNull()) {
        thresholdType = v.toFloat()>0.5f ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    }

}

void Threshold::apply(Layer* in, Layer* out, Layer* mask) {
    cv::threshold(*in, *out, t, 255, thresholdType);
    applyMask(in, out, mask);
}
