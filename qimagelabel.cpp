#include "qimagelabel.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QDebug>

QImageLabel::QImageLabel(QWidget *parent): QLabel(parent)
{

}

QImageLabel::~QImageLabel()
{

}

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
    double angle = atan(vec.y() / vec.x());
    trans.rotateRadians(angle);
    QPixmap pixelMap = pixmap()->transformed(trans);
    setPixmap(pixelMap);**/
    boundingRect.updateRectPosition(event->pos());
}

void QImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    boundingRect.setRectDimensions();
}
