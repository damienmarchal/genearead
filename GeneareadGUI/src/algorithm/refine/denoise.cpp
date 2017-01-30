#include <header/algorithm/refine/denoise.h>

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

Denoise::Denoise()
    : h(3.0f)
{

}

QString Denoise::getName() {
    return "denoise";
}

void Denoise::setParameters(QObject* parameters) {

}

void Denoise::apply(Layer* in, Layer* out, Layer* mask) {
    cv::fastNlMeansDenoising(*in, *out, 10, 7, 21);
}
