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

    /**
     * @brief bernsen
     * Applies bernsen algorithm to a layer
     * @deprecated use applyText with correct arguments
     * @param image the layer on which to apply
     * @return the binarized layer
     */
    Layer* bernsen(Layer* image);

    /**
     * @brief laab
     * Applies LAAB algorithm to a layer
     * @deprecated use applyText with correct arguments
     * @param image the layer on which to apply
     * @return the binarized layer
     */
    Layer* laab   (Layer* image);

    /**
     * @brief laab
     * Applies LAAB algorithm to a layer
     * @deprecated use applyText with correct arguments
     * @param image the layer on which to apply
     * @return the binarized layer
     */
    Layer* niblack(Layer* image);

    /**
     * @brief RGBToGray
     * Converts a CV_8UC3 layer into a CV_8UC1 layer.
     * @param RGBMatrix the input matrix
     * @param GrayMatrix the output matrix
     */
    void RGBToGray(Layer* RGBMatrix, Layer* GrayMatrix);

    /**
     * @brief GrayToRGB
     * Converts a CV_8UC1 layer into a CV_8UC3 layer.
     * @param GrayMatrix the input matrix
     * @param RGBMatrix the output matrix
     */
    void GrayToRGB(Layer* GrayMatrix, Layer* RGBMatrix);

    /**
     * @brief getLineAlgorithms
     * @return the list of all line algorithms availables.
     */
    LineAlgorithms getLineAlgorithms();

    /**
     * @brief getTextAlgorithms
     * @return the list of all text algorithms availables.
     */
    TextAlgorithms getTextAlgorithms();

    /**
     * @brief getRefineAlgorithms
     * @return the list of all refine algorithms availables.
     */
    RefineAlgorithms getRefineAlgorithms();


signals:

public slots:

protected:

    /**
     * @brief grayInMatrix
     * The CV_8UC1 matrix that contains gray, non-binarized data.
     * Is converted from CV_8UC3 from an image matrix from the calling ImageManager.
     */
    Layer grayInMatrix;

    /**
     * @brief grayOutMatrix
     * The CV_8UC1 matrix that contains black and white, binarized data.
     * Is converted to CV_8UC3 for the calling ImageManager.
     */
    Layer grayOutMatrix;

    TextAlgorithms textAlgorithms;
    LineAlgorithms lineAlgorithms;
    RefineAlgorithms refineAlgorithms;

    /**
     * @brief getTextAlgorithm
     * @param name the algorithm name
     * @return a pointer to a text algorithm named <code>name</code>.
     * If no such algorithm exists, return NULL.
     */
    TextAlgorithm* getTextAlgorithm(QString name);

    /**
     * @brief getLineAlgorithm
     * @param name the algorithm name
     * @return a pointer to a line algorithm named <code>name</code>.
     * If no such algorithm exists, return NULL.
     */
    LineAlgorithm* getLineAlgorithm(QString name);

    /**
     * @brief getRefineAlgorithm
     * @param name the algorithm name
     * @return a pointer to a refine algorithm named <code>name</code>.
     * If no such algorithm exists, return NULL.
     */
    RefineAlgorithm* getRefineAlgorithm(QString name);

    /**
     * @brief updateGrayLayer
     * Allocates new grayInMatrix and grayOutMatrix if needed.
     * The reallocation condition is the the size of RGBImage.
     * If RGBImage have a different number of cols or rows, memory is reallocated to fit. Not otherwise.
     * @param RGBImage the reference matrix
     */
    void updateGrayLayer(Layer* RGBImage);
};

#endif // ALGORITHMMANAGER_H
