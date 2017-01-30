#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QObject>
#include <QImage>
#include <QDebug>

#include "text/textAlgorithm.h"
#include "line/lineAlgorithm.h"
#include "refine/refineAlgorithm.h"

typedef std::vector<TextAlgorithm*> TextAlgorithms;
typedef std::vector<LineAlgorithm*> LineAlgorithms;
typedef std::vector<RefineAlgorithm*> RefineAlgorithms;

class AlgorithmManager {

public:
    explicit AlgorithmManager();

    void applyText(Layer* RGBMatrix, Layer* mask, QObject* parameters);
    void applyLine(Layer* RGBMatrix, Layer* mask, QObject* parameters);
    void applyRefine(Layer* RGBMatrix, Layer* mask, QObject* parameters);

    /**
     * implementation found at "http://stackoverflow.com/a/22389696"
     * @brief bernsen
     * @param image
     */
    Layer* lines(Layer* image);

    Layer* bernsen(Layer* image);
    Layer* laab   (Layer* image);
    Layer* niblack(Layer* image);

    void RGBToGray(Layer* RGBMatrix, Layer* GrayMatrix);
    void GrayToRGB(Layer* GrayMatrix, Layer* RGBMatrix);

    LineAlgorithms getLineAlgorithms();
    TextAlgorithms getTextAlgorithms();
    RefineAlgorithms getRefineAlgorithms();


signals:

public slots:

protected:
    Layer grayInMatrix;
    Layer grayOutMatrix;

    TextAlgorithms textAlgorithms;
    LineAlgorithms lineAlgorithms;
    RefineAlgorithms refineAlgorithms;

    TextAlgorithm* getTextAlgorithm(QString name);
    LineAlgorithm* getLineAlgorithm(QString name);
    RefineAlgorithm* getRefineAlgorithm(QString name);

    void updateGrayLayer(Layer* RGBImage);
};

#endif // ALGORITHMMANAGER_H
