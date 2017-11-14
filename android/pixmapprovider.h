#ifndef PIXMAPPROVIDER_H
#define PIXMAPPROVIDER_H

#include <QQuickImageProvider>
#include "pixmap.h"

class PixmapProvider : public QQuickImageProvider
{
public:
    PixmapProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // PIXMAPPROVIDER_H
