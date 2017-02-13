#include <header/algorithm/algorithmManager.h>

#include <header/algorithm/text/adaptiveThreshold.h>
#include <header/algorithm/text/niblack.h>
#include <header/algorithm/text/sauvola.h>
#include <header/algorithm/text/threshold.h>

#include <header/algorithm/refine/blur.h>
#include <header/algorithm/refine/denoise.h>
#include <header/algorithm/refine/dilate.h>
#include <header/algorithm/refine/erode.h>

#include <iostream>

AlgorithmManager::AlgorithmManager() {
    textAlgorithms = TextAlgorithms();
    textAlgorithms.push_back(new AdaptiveThreshold());
    textAlgorithms.push_back(new Niblack());
    textAlgorithms.push_back(new Sauvola());
    textAlgorithms.push_back(new Threshold());

    lineAlgorithms = LineAlgorithms();

    refineAlgorithms = RefineAlgorithms();
    refineAlgorithms.push_back(new Blur());
    refineAlgorithms.push_back(new Denoise());
    refineAlgorithms.push_back(new Dilate());
    refineAlgorithms.push_back(new Erode());
}

LineAlgorithms AlgorithmManager::getLineAlgorithms() {return lineAlgorithms;}
TextAlgorithms AlgorithmManager::getTextAlgorithms() {return textAlgorithms;}
RefineAlgorithms AlgorithmManager::getRefineAlgorithms() {return refineAlgorithms;}

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
    for(unsigned i=0; i<textAlgorithms.size(); ++i) {
        a = textAlgorithms[i];
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
    QVariant v;
    if((v = parameters->property("textAlgoName")).isNull())
        return;
    TextAlgorithm* algo = getTextAlgorithm(v.toString());
    if(algo == NULL)
        return;
    algo->setParameters(parameters);
    updateGrayLayer(RGBMatrix);
    RGBToGray(RGBMatrix, &grayInMatrix);
    algo->apply(&grayInMatrix, &grayOutMatrix, mask);
    GrayToRGB(&grayOutMatrix, RGBMatrix);
}

void AlgorithmManager::applyRefine(Layer* RGBMatrix, Layer* mask, QObject* parameters) {
    QVariant v;
    if((v = parameters->property("refineAlgoName")).isNull())
        return;
    RefineAlgorithm* algo = getRefineAlgorithm(v.toString());
    if(algo == NULL)
        return;
    algo->setParameters(parameters);
    updateGrayLayer(RGBMatrix);
    RGBToGray(RGBMatrix, &grayInMatrix);
    algo->apply(&grayInMatrix, &grayOutMatrix, mask);
    GrayToRGB(&grayOutMatrix, RGBMatrix);
}

void AlgorithmManager::applyLine(Layer* RGBMatrix, Layer* mask, QObject* parameters) {

}
