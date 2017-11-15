#include <QPixmap>
#include <QImageWriter>
#include "pixmap.h"
#include "util.h"

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
        return "image://pixmap/" + temp_url;
    else
        return QString();
}


void Pixmap::load(QString url){
    QPixmap * old = nullptr;
    this->original_url = this->temp_url = url;
    if (pixmap)
        old = pixmap;
    qDebug("Loading Image...");
    pixmap =  new QPixmap(url);
    emit dataChanged();
    if (old)
        delete old;
}

void Pixmap::clear(){
    if (pixmap)
        delete pixmap;
    pixmap = nullptr;
    original_url = temp_url = QString();
    emit dataChanged();
}

void Pixmap::crop(const float x, const float y, const float width, const float height){
//    qDebug(QString::number(x).toLatin1());
//    qDebug(QString::number(y).toLatin1());
//    qDebug(QString::number(width).toLatin1());
//    qDebug(QString::number(height).toLatin1());
    QPixmap * old = nullptr;
    if (pixmap)
        old = pixmap;
    QPixmap cropped = pixmap->copy(x, y, width, height);
    pixmap = new QPixmap(cropped);
    temp_url = QString::fromStdString(extractPath(temp_url.toStdString()) + "/.qAndroidcache.jpg");
    saveFileAs(temp_url);
    qDebug(temp_url.toLatin1());
    emit dataChanged();
    if(old)
        delete old;
}

void Pixmap::save()
{
    saveFileAs(original_url);
}

void Pixmap::reset(){
    if(pixmap)
        delete pixmap;
    pixmap = new QPixmap(original_url);
    temp_url = original_url;
    emit dataChanged();
}

void Pixmap::saveFileAs(QString &imageFileName){
    QImageWriter writer(imageFileName);
    if(writer.write(pixmap->toImage()))
        qDebug("Image saved");
}
