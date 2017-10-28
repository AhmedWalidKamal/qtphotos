#include "qimagelabel.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

QImageLabel::QImageLabel(QWidget *parent): QLabel(parent)
{
    rotation = 0;
    originalPixmap = nullptr;
}

QImageLabel::~QImageLabel()
{
    delete originalPixmap;
}

void QImageLabel::setPixmap(QPixmap &pixelmap) {
    QLabel::setPixmap(pixelmap);
    originalPixmap = new QPixmap(pixelmap);
}

void QImageLabel::setPixmap(QPixmap &&pixelmap) {
    setPixmap(pixelmap);
}

void QImageLabel::mousePressEvent(QMouseEvent *event)
{
    if (!pixmap())
        return;
    boundingRect.initBoundingRectangle(event->pos(), this);
}

void QImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!pixmap())
        return;
    qDebug() << "Entered Mouse Move";
    //WARNING USE THIS SHIT!!!
//    QTransform trans;
//    QPoint endPoint = event->pos();
//    QPoint startingPoint = pos();
//    startingPoint.setX(startingPoint.x() +  width() / 2.0);
//    startingPoint.setY(startingPoint.y() +  height() / 2.0);
//    QPoint vec = endPoint - startingPoint;
//    double angle = qAtan2(vec.y(), vec.x());
//    double imageHeight = originalPixmap->height();
//    double imageWidth = originalPixmap->width();
//    trans.translate(imageWidth / 2.0, imageHeight / 2.0);
//    //Qt::Axis axis;
//    trans.rotateRadians(angle);
//    qDebug() << "Center of Gravity: " << QPoint(imageWidth / 2.0, imageHeight / 2.0) << " Rotation Angle: " << angle;
//    trans.translate(-imageWidth / 2.0, -imageHeight / 2.0);
//    QPixmap pixelMap(*originalPixmap);
//    pixelMap = pixelMap.transformed(trans, Qt::TransformationMode::SmoothTransformation);
//    qDebug() << originalPixmap->rect() << "new: " << pixelMap.rect();
//    QLabel::setPixmap(pixelMap);
    boundingRect.updateRectPosition(event->pos());
}

void QImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (!pixmap())
        return;
    boundingRect.setRectDimensions();
    qDebug() << "Selected Area: " << boundingRect.getBoundingRect();
}

void QImageLabel::crop() {
    if (!pixmap())//need to check if bounding rect is empty;
        return;
    double imageHeight = pixmap()->height();
    double imageWidth = pixmap()->width();
    double scaleX = imageWidth / width();
    double scaleY = imageHeight / height();
    boundingRect.scale(scaleX, scaleY);
    qDebug() << "Selected Area After Scaling: " << boundingRect.getBoundingRect();
    QPixmap cropped = pixmap()->copy(boundingRect.getBoundingRect());
    setPixmap(cropped);
    boundingRect.reset();
}
