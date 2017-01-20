#include "imageprovider.h"
#include "imagemanager.h"

ImageProvider::ImageProvider(ImageManager *imageManager)
    : QQuickImageProvider(QQmlImageProviderBase::Image)
{
    this->imageManager = imageManager;
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    qDebug() << "image request";
    return this->imageManager->getImage();
}
