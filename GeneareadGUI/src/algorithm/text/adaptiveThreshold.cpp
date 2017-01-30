#include <header/algorithm/text/adaptiveThreshold.h>

AdaptiveThreshold::AdaptiveThreshold()
    : w(5)
    , C(2)
    , thresholdType(cv::THRESH_BINARY)
    , adaptiveMethod(cv::ADAPTIVE_THRESH_MEAN_C)
{

}

QString AdaptiveThreshold::getName() {
    return "adaptiveThreshold";
}

void AdaptiveThreshold::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("w")).isNull()) {
        w = v.toInt();
    }

    if(!(v = parameters->property("inv")).isNull()) {
        thresholdType = v.toBool() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    }

    if(!(v = parameters->property("mean")).isNull()) {
        adaptiveMethod = v.toBool() ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
    }

}

void AdaptiveThreshold::apply(Layer* in, Layer* out, Layer* mask) {
    cv::adaptiveThreshold(*in, *out, 255, adaptiveMethod, thresholdType, w, C);
    applyMask(in, out, mask);
}
