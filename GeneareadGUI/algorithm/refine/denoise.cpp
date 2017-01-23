#include "denoise.h"

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
    qDebug() << "DENOISE" << h;
    std::cout << *out << std::endl;
    cv::fastNlMeansDenoising(*in, *out, 10, 7, 21);
    std::cout << *out << std::endl;
}
