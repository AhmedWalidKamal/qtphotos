#ifndef BACKEND_H
#define BACKEND_H

#include <QtWidgets>
#include <QLabel>

class BackEnd : public QObject
{
    Q_OBJECT
public:
    explicit BackEnd(QObject *parent = nullptr);

    // Added functions:
    Q_INVOKABLE QString openImage();

private:
    QImage currentImage;

signals:

public slots:
};

#endif // BACKEND_H
