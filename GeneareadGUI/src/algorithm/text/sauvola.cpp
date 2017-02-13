#include <header/algorithm/text/sauvola.h>
#include <header/algorithm/text/niblackDerivedAlgorithm.h>

Sauvola::Sauvola()
    : NiblackDerivedAlgorithm()
    , k(0.2) //[0.2, 0.5]
    , r(128) //middle grayscale
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
        k = (v.toDouble()*0.3)+0.2;
    }

    if(!(v = parameters->property("r")).isNull()) {
        r = std::round(v.toDouble()*255);
    }

}

double Sauvola::threshold(double m, double s, double min_I, double max_I, double max_S) {
    return m * (1 + k*(s/r-1));
}
