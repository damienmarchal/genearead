#include "sauvola.h"
#include "niblackDerivedAlgorithm.h"

Sauvola::Sauvola()
    : NiblackDerivedAlgorithm()
    , k(0.2) //[0.2, 0.5]
    , R(128) //middle grayscale
{

}

QString Sauvola::getName() {
    return "sauvola";
}

void Sauvola::setParameters(QObject* parameters) {
    QVariant v;

    if(!(v = parameters->property("w")).isNull()) {
        winx = v.toInt();
        winy = winx;
    }

    if(!(v = parameters->property("k")).isNull()) {
        k = v.toDouble();
    }

    if(!(v = parameters->property("R")).isNull()) {
        R = v.toDouble();
    }

}

double Sauvola::threshold(double m, double s, double min_I, double max_I, double max_S) {
    return m * (1 + k*(s/R-1));
}


