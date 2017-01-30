#include "kernelFilter.h"

#include <opencv2/imgproc/imgproc.hpp>

KernelFilter::KernelFilter()
    : kernel(Layer())
    , ddepth(CV_8U)
    , anchor(cv::Point(-1, -1))
    , borderType(cv::BORDER_CONSTANT)
{

}

QString KernelFilter::getName() {
    return "filter";
}

void KernelFilter::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("kernel")).isNull()) {

    }

}

void KernelFilter::apply(Layer* in, Layer* out, Layer* mask) {
    cv::filter2D(*in, *out, ddepth, kernel, anchor, delta, borderType);
}
