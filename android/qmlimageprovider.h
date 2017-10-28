#ifndef QMLIMAGEPROVIDER_H
#define QMLIMAGEPROVIDER_H


class QmlImageProvider : public QObject, QQuickImageProvider
{
    Q_OBJECT
public:
    QmlImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

public slots:
    void loadImg(QImage img);

private:
    QImage img;
};

#endif // QMLIMAGEPROVIDER_H
