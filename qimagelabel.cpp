#include "qimagelabel.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

QImageLabel::QImageLabel(QWidget *parent): QLabel(parent)
{

}

QImageLabel::~QImageLabel()
{

}

//void QImageLabel::setPixmap(QPixmap &pixmap) {
//    QLabel::setPixmap(pixmap);
//}

void QImageLabel::mousePressEvent(QMouseEvent *event)
{
    boundingRect.initBoundingRectangle(event->pos(), this);
}

void QImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Entered Mouse Move";
    //WARNING DON'T USE THIS SHIT!!!
    /**QTransform trans;
    QPoint endPoint = event->pos();
    QPoint startingPoint = pos();
    startingPoint.setX(startingPoint.x() +  width() / 2.0);
    startingPoint.setY(startingPoint.y() +  height() / 2.0);
    QPoint vec = endPoint - startingPoint;
    double angle = qAtan2(vec.y(), vec.x());
    trans.rotateRadians(angle);
    QPixmap pixelMap = pixmap()->transformed(trans);
    setPixmap(pixelMap);**/
    boundingRect.updateRectPosition(event->pos());
}

void QImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    boundingRect.setRectDimensions();
    qDebug() << boundingRect.getBoundingRect();
}

void QImageLabel::crop() {
    double imageHeight = pixmap()->height();
    double imageWidth = pixmap()->width();
    double scaleX = imageWidth / width();
    double scaleY = imageHeight / height();
    boundingRect.scale(scaleX, scaleY);
    QPixmap cropped = pixmap()->copy(boundingRect.getBoundingRect());
    setPixmap(cropped);
    boundingRect.reset();
}
