#include "imageProvider.h"
#include "imageManager.h"

#include <QDebug>

ImageProvider::ImageProvider(ImageManager *imageManager)
    : QQuickImageProvider(QQmlImageProviderBase::Image)
{
    this->imageManager = imageManager;
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {

    if(id == "main") {
        qDebug() << "main refresh ";
        return imageManager->getImage();
    }

    QString previewSlide = "preview";
    if(id.startsWith(previewSlide)) {
        int allSize = id.size();
        int position = previewSlide.size();
        int n = allSize - position;

        int previewID = id.mid(position, n).toInt();
        qDebug() << "preview refresh" << previewID;
        return imageManager->getPreview(previewID);
    }

    qDebug() << "not found " + id;
    return QImage();
}
