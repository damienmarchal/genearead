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
        w = (std::round(v.toFloat()*4.0f)+1)*2+1;
    }

    if(!(v = parameters->property("inv_mean")).isNull()) {
        float vf = v.toFloat();
        thresholdType = vf>0.5f ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
        adaptiveMethod = vf<=0.25f || vf>0.75f ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
    }

    /*if(!(v = parameters->property("mean")).isNull()) {
        float vf = v.toFloat();
    }*/

}

void AdaptiveThreshold::apply(Layer* in, Layer* out, Layer* mask) {
    cv::adaptiveThreshold(*in, *out, 255, adaptiveMethod, thresholdType, w, C);
    applyMask(in, out, mask);
}
