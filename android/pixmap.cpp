#include <QPixmap>
#include <QImageWriter>
#include "pixmap.h"

Pixmap::Pixmap(QObject *parent) : QObject(parent), pixmap(nullptr)
{

}

Pixmap::~Pixmap()
{
    if (pixmap)
        delete pixmap;
}

QString Pixmap::data(){
    qDebug("Data requested");
    if (pixmap)
        return "image://pixmap/" + url;
    else
        return QString();
}


void Pixmap::load(QString url){
    QPixmap * old = nullptr;
    this->url = url;
    if (pixmap)
        old = pixmap;
    qDebug("Loading Image...");
    pixmap = new QPixmap(url);
    emit dataChanged();
    if (old)
        delete old;
}

void Pixmap::clear(){
    if (pixmap)
        delete pixmap;
    pixmap = nullptr;
    emit dataChanged();
}

void Pixmap::crop(const float x, const float y, const float width, const float height){
    qDebug(QString::number(x).toLatin1());
    qDebug(QString::number(y).toLatin1());
    qDebug(QString::number(width).toLatin1());
    qDebug(QString::number(height).toLatin1());
    QPixmap * old = nullptr;
    if (pixmap)
        old = pixmap;

    QPixmap cropped = pixmap->copy(x, y, width, height);
    pixmap = new QPixmap(cropped);
    // url = QString("/storage/emulated/0/Pictures/Screenshots/hesham.jpg");
    save(url);
    qDebug(url.toLatin1());
    emit dataChanged();
    if(old)
        delete old;
}

void Pixmap::save(QString &imageFileName)
{
    QImageWriter writer(imageFileName);
    if(writer.write(pixmap->toImage()))
        qDebug("Image saved");
}

