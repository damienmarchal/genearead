#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QDebug>

class algorithm : public QObject
{
    Q_OBJECT
public:
    explicit algorithm(QObject *parent = 0);
    Q_INVOKABLE QString apply(QObject *image, qint32 code) {
        switch(code) {
        case(0) : this->bernsen(image); break;
        case(1) : this->laab(image); break;
        case(2) : this->lines(image); break;
        default : break;
        }
        qDebug() << "received : " << code;
        return QString(code);
    }

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
