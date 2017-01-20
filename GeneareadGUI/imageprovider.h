#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

#include "imageprovider.h"
#include "imagemanager.h"

class ImageProvider : public QQuickImageProvider
{

public:
    ImageProvider(ImageManager *imageManager);
    QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize);

protected:

private:
    ImageManager *imageManager;

};

#endif // IMAGEPROVIDER_H
