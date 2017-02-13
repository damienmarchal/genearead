#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

#include "imageManager.h"

/**
 * @brief The ImageProvider class provides QImage objects from an ImageManager.
 * The requested id of method requestImage determines the content of the QImage.
 * Is used for the main ImageManager workspace image and for its previews.
 */
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
