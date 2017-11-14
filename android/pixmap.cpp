#include <QPixmap>
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
    pixmap = new QPixmap("file://" + url);
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

