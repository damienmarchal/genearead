#include "threshold.h"

Threshold::Threshold()
{

}

QString Threshold::getName() {
    return "threshold";
}

void Threshold::setParameters(QObject* parameters) {

}

void Threshold::apply(Layer* in, Layer* out, Layer* mask) {
    uchar p;
    for(int i=0; i<in->cols; i++) {
        for(int j=0; j<in->rows; j++) {
            p = in->at<uchar>(j, i);
            if(p>128)
                out->at<uchar>(j, i) = 255;
            else
                out->at<uchar>(j, i) = 0;
        }
    }
}

