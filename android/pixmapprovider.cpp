#include "pixmapprovider.h"

PixmapProvider::PixmapProvider(): QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap PixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    QPixmap image(id);
    QPixmap result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;
}
