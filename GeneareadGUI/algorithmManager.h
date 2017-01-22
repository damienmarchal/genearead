#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QObject>
#include <QImage>
#include <QDebug>

#include <algorithm/algorithm.h>
#include <algorithm/bernsen.h>

typedef std::vector<Algorithm*> Algorithms;

class AlgorithmManager {

public:
    explicit AlgorithmManager();

    void binarize(Layer *RGBMatrix, Layer *mask, QObject* parameters);

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

signals:

public slots:

protected:
    Layer grayInMatrix;
    Layer grayOutMatrix;
    Algorithms algorithms;

    Algorithm* getAlgorithm(QString name);
    void updateGrayLayer(Layer *RGBImage);
};

#endif // ALGORITHMMANAGER_H
