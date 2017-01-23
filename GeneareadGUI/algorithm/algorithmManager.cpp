#include "algorithmManager.h"
#include "text/niblack.h"
#include "text/sauvola.h"
#include "refine/denoise.h"

#include <iostream>

AlgorithmManager::AlgorithmManager() {
    textAlgorithms = TextAlgorithms();
    textAlgorithms.push_back(new Niblack());
    textAlgorithms.push_back(new Sauvola());

    lineAlgorithms = LineAlgorithms();

    refineAlgorithms = RefineAlgorithms();
    refineAlgorithms.push_back(new Denoise());
}

void AlgorithmManager::updateGrayLayer(Layer* RGBMatrix) {
    const int rows = RGBMatrix->rows;
    const int cols = RGBMatrix->cols;
    if(
            &grayInMatrix==NULL ||
            cols != grayInMatrix.cols ||
            rows != grayInMatrix.rows) {
        grayInMatrix = Layer(rows, cols, CV_8UC1);
        grayOutMatrix = Layer(rows, cols, CV_8UC1);
    }

    cvtColor(*RGBMatrix, grayInMatrix, CV_RGB2GRAY);
}

void AlgorithmManager::RGBToGray(Layer* RGBMatrix, Layer* grayMatrix) {
    cvtColor(*RGBMatrix, *grayMatrix, CV_RGB2GRAY);
}

void AlgorithmManager::GrayToRGB(Layer* grayMatrix, Layer* RGBMatrix) {
    cvtColor(*grayMatrix, *RGBMatrix, CV_GRAY2RGB);
}

TextAlgorithm* AlgorithmManager::getTextAlgorithm(QString name) {
    TextAlgorithm* a;
    qDebug() << "!   searching through" << textAlgorithms.size() << "algorithm(s)";
    for(unsigned i=0; i<textAlgorithms.size(); ++i) {
        qDebug() << " -> testing number" << i;
        a = textAlgorithms[i];
        qDebug() << "    looking for" << name << ". Got" << a->getName();
        if(a->getName() == name)
            return a;
    }
    return NULL;
}

/*LineAlgorithm* AlgorithmManager::getLineAlgorithm(QString name) {
    LineAlgorithm* a;
    for(unsigned i=0; i<lineAlgorithms.size(); ++i) {
        a = lineAlgorithms[i];
        if(a->getName() == name)
            return a;
    }
    return NULL;
}*/

RefineAlgorithm* AlgorithmManager::getRefineAlgorithm(QString name) {
    RefineAlgorithm* a;
    for(unsigned i=0; i<refineAlgorithms.size(); ++i) {
        a = refineAlgorithms[i];
        if(a->getName() == name)
            return a;
    }
    return NULL;
}

void AlgorithmManager::applyText(Layer* RGBMatrix, Layer* mask, QObject* parameters) {

    qDebug() << "--- applying binary";
    qDebug() << "--- --- reading algorithm name";
    QVariant v;
    if((v = parameters->property("name")).isNull())
        return;
    qDebug() << "--- [V] reading algorithm name";

    const QString name = v.toString();
    qDebug() << "--- --- fetching algorithm :" << name;
    TextAlgorithm* algo = getTextAlgorithm(name);
    if(algo == NULL) {
        qDebug() << "--- --- <X> fetching algorithm :" << name;
        return;
    }
    qDebug() << "--- [V] fetching algorithm :" << name;

    qDebug() << "--- --- setting parameters";
    algo->setParameters(parameters);
    qDebug() << "--- [V] setting parameters";

    qDebug() << "--- --- update gray buffers";
    updateGrayLayer(RGBMatrix);
    qDebug() << "--- [V] update gray buffers";


    qDebug() << "--- --- converting RGB to Gray";
    RGBToGray(RGBMatrix, &grayInMatrix);
    qDebug() << "--- [V] converting RGB to Gray";


    qDebug() << "--- --- binarizing";
    algo->apply(&grayInMatrix, &grayOutMatrix, mask);
    qDebug() << "--- [V] binarizing";

    qDebug() << "--- --- converting Gray to RGB";
    GrayToRGB(&grayOutMatrix, RGBMatrix);
    qDebug() << "--- [V] converting Gray to RGB";

    qDebug() << "[V] applying binary";
}

void AlgorithmManager::applyRefine(Layer* RGBMatrix, Layer* mask, QObject* parameters) {

    qDebug() << "--- applying refining";
    qDebug() << "--- --- reading algorithm name";
    QVariant v;
    if((v = parameters->property("name")).isNull())
        return;
    qDebug() << "--- [V] reading algorithm name";

    const QString name = v.toString();
    qDebug() << "--- --- fetching algorithm :" << name;
    RefineAlgorithm* algo = getRefineAlgorithm(name);
    if(algo == NULL) {
        qDebug() << "--- --- <X> fetching algorithm :" << name;
        return;
    }
    qDebug() << "--- [V] fetching algorithm :" << name;

    qDebug() << "--- --- setting parameters";
    algo->setParameters(parameters);
    qDebug() << "--- [V] setting parameters";

    qDebug() << "--- --- update gray buffers";
    updateGrayLayer(RGBMatrix);
    qDebug() << "--- [V] update gray buffers";


    qDebug() << "--- --- converting RGB to Gray";
    RGBToGray(RGBMatrix, &grayInMatrix);
    qDebug() << "--- [V] converting RGB to Gray";


    qDebug() << "--- --- binarizing";
    algo->apply(&grayInMatrix, &grayOutMatrix, mask);
    qDebug() << "--- [V] binarizing";

    qDebug() << "--- --- converting Gray to RGB";
    GrayToRGB(&grayOutMatrix, RGBMatrix);
    qDebug() << "--- [V] converting Gray to RGB";

    qDebug() << "[V] applying binary";
}

void AlgorithmManager::applyLine(Layer* RGBMatrix, Layer* mask, QObject* parameters) {

}

Layer* AlgorithmManager::bernsen(Layer* image) {
    Layer ret = Layer::zeros(image->size(),image->type());
    return &ret;
}

Layer* AlgorithmManager::laab(Layer *image) {
    //image->setProperty("color", "green");
    return image;
}

Layer* AlgorithmManager::lines(Layer *image) {
    //image->setProperty("color", "black");
    return image;
}



/**************************************************************
 * Binarization with several methods
 * (0) Niblacks method
 * (1) Sauvola & Co.
 *     ICDAR 1997, pp 147-152
 * (2) by myself - Christian Wolf
 *     Research notebook 19.4.2001, page 129
 * (3) by myself - Christian Wolf
 *     20.4.2007
 *
 * See also:
 * Research notebook 24.4.2001, page 132 (Calculation of s)
 **************************************************************/

/*

            case NIBLACK:
                th = m + k*s;
                break;

            case SAUVOLA:
                th = m * (1 + k*(s/dR-1));
                break;

            case WOLFJOLION:
                th = m + k * (s/max_s-1) * (m-min_I);
                break;

*/
