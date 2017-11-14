#include "qimagelabel.h"
#include "mathutil.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

QImageLabel::QImageLabel(QWidget *parent): QLabel(parent)
{
    rotationDiff = 0;
    curRotation = 0;
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

QImageLabel::State QImageLabel::getState()
{
    return currState;
}

void QImageLabel::setState(QImageLabel::State state)
{
    currState = state;
}

void QImageLabel::resetBoundingRectangle()
{
    boundingRect.reset();
}

void QImageLabel::mousePressEvent(QMouseEvent *event)
{
    switch(currState) {
    case SELECTING:
        if (!boundingRect.isEmpty() && boundingRect.contains(event->pos())) {
            boundingRect.initMoving(event->pos());
        } else {
            boundingRect.initBoundingRectangle(event->pos(), this);
        }
        break;
    case ROTATING: {
        QPoint endPoint = event->pos();
        QPoint startingPoint = pos();
        startingPoint.setX(startingPoint.x() +  width() / 2.0);
        startingPoint.setY(startingPoint.y() +  height() / 2.0);
        rotationDiff = curRotation - math::calculateAngle(startingPoint, endPoint);
        if (!pixmap())
            return;
        break;
    }
    default:
        break;
    }
}

void QImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!pixmap())
        return;
    switch(currState) {
    case SELECTING:
        if (boundingRect.rubberBandIsMoving()) {
            boundingRect.moveRubberBand(event->pos());
        }
        boundingRect.updateRectPosition(event->pos());
        break;
    case ROTATING: {
        qDebug() << "Rotating: Entered Mouse Move";
        QTransform trans;
        QPoint endPoint = event->pos();
        QPoint startingPoint = pos();
        startingPoint.setX(startingPoint.x() +  width() / 2.0);
        startingPoint.setY(startingPoint.y() +  height() / 2.0);
        double angle = math::calculateAngle(startingPoint, endPoint);
        double imageHeight = originalPixmap->height();
        double imageWidth = originalPixmap->width();
        trans.translate(imageWidth / 2.0, imageHeight / 2.0);
        trans.rotateRadians(angle + rotationDiff);
        curRotation = angle + rotationDiff;
        qDebug() << "Center of Gravity: " << QPoint(imageWidth / 2.0, imageHeight / 2.0) << " Rotation Angle: " << angle;
        trans.translate(-imageWidth / 2.0, -imageHeight / 2.0);
        QPixmap pixelMap(*originalPixmap);
        pixelMap = pixelMap.transformed(trans, Qt::TransformationMode::SmoothTransformation);
        qDebug() << originalPixmap->rect() << "new: " << pixelMap.rect();
        QLabel::setPixmap(pixelMap);
        break;
    }
    default:
        break;
    }
}

void QImageLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (!pixmap())
        return;
    switch(currState) {
    case SELECTING:
        if (boundingRect.rubberBandIsMoving()) {
            boundingRect.stopMoving();
        } else {
            boundingRect.setupBoundingRect();
        }
        qDebug() << "Selected Area: " << boundingRect.getBoundingRect();
        break;
    case ROTATING:
        break;
    default:
        break;
    }
}

void QImageLabel::crop() {
    if (!pixmap() || boundingRect.isEmpty()) {
        return;
    }
    if (!boundingRect.validSize()) {
        boundingRect.reset();
        return;
    }
    double imageHeight = pixmap()->height();
    double imageWidth = pixmap()->width();
    double scaleX = imageWidth / width();
    double scaleY = imageHeight / height();
    boundingRect.scale(scaleX, scaleY);
//    qDebug() << "Selected Area After Scaling: " << boundingRect.getBoundingRect();
    QPixmap cropped = pixmap()->copy(boundingRect.getBoundingRect());
    setPixmap(cropped);
    boundingRect.reset();
}

void QImageLabel::zoomIn() {
    switch (currState) {
    case ACTIVE:
        break;
    case SELECTING:
        break;
    default:
        break;
    }
}

void QImageLabel::zoomOut() {
    switch (currState) {
    case ACTIVE:
        break;
    case SELECTING:
        break;
    default:
        break;
    }
}
