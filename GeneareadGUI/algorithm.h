#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QImage>
#include <QDebug>

#include <opencv2/core.hpp>

typedef cv::Point3_<unsigned char> Pixel;

class algorithm : public QObject
{
    Q_OBJECT

public:
    explicit algorithm(QObject *parent = 0);
    Q_INVOKABLE QString apply(QObject *image, qint32 code);

signals:

public slots:

protected:

    /**
     * implementation found at "http://stackoverflow.com/a/22389696"
     * @brief bernsen
     * @param image
     */
    void bernsen(QObject *image);

    void laab(QObject *image);

    void lines(QObject *image);
};

#endif // ALGORITHM_H
