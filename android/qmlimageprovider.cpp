#include "qmlimageprovider.h"
#include <QDebug>

QmlImageProvider::QmlImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QmlImage QmlImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    if (img.isNull())
        qDebug("Error in providing an image!");
    return img;
}

void QmlImageProvider::loadImg(QImage img)
{
    this->img = img;
}
