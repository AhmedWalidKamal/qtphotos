#include "qimagelabel.h"
#include "mathutil.h"

#include <QMouseEvent>
#include <QDebug>
#include <QtMath>

QImageLabel::QImageLabel(QWidget *parent): QLabel(parent)
{
    rotationDiff = 0;
    curRotation = 0;
    resizedPixmap = nullptr;
    originalPixmap = nullptr;
    scale = 1;
    setMinimumSize(1, 1);
}

QImageLabel::~QImageLabel()
{
    delete resizedPixmap;
    delete originalPixmap;
}

void QImageLabel::setPixmap(QPixmap &pixelmap) {
    QLabel::setPixmap(pixelmap);
//    resize(pixelmap.size());
    delete originalPixmap;
    delete resizedPixmap;
    resizedPixmap = new QPixmap(pixelmap);
    originalPixmap = new QPixmap(pixelmap);
    qDebug() << "Size Hint: " << sizeHint();
    currState = ACTIVE;
    curRotation = 0;
    rotationDiff = 0;
    scale = 1;
    adjustSize();
    updateGeometry();
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
        QPoint startingPoint = QPoint(width() / 2.0, height() / 2.0);
        qDebug() << "Pos" << pos() <<  "Start" << startingPoint << "End" << endPoint;
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
        QPoint startingPoint = QPoint(width() / 2.0, height() / 2.0);
        double angle = math::calculateAngle(startingPoint, endPoint);
        double imageHeight = resizedPixmap->height();
        double imageWidth = resizedPixmap->width();
        trans.translate(imageWidth / 2.0, imageHeight / 2.0);
        trans.rotateRadians(angle + rotationDiff);
        curRotation = angle + rotationDiff;
        qDebug() << "Center of Gravity: " << QPoint(imageWidth / 2.0, imageHeight / 2.0) << " Rotation Angle: " << angle;
        trans.translate(-imageWidth / 2.0, -imageHeight / 2.0);
        QPixmap pixelMap(*resizedPixmap);
        pixelMap = pixelMap.transformed(trans, Qt::TransformationMode::SmoothTransformation);
        QLabel::setPixmap(pixelMap);
        adjustSize();
        resize(scale * pixelMap.size());
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
    QLabel::setPixmap(cropped);
    delete resizedPixmap;
    resizedPixmap = new QPixmap(cropped);
    boundingRect.reset();
    adjustSize();
}

void QImageLabel::zoom(double ratio, bool isZoomIn) {
    switch (currState) {
    case ACTIVE: {
        //scale = ratio / scale;
        //qDebug() << scale * pixmap()->size();
        //QPixmap newMap = *pixmap();
        //newMap = newMap.scaled(scale * newMap.size(), Qt::KeepAspectRatio);
        //qDebug() << newMap.size();
        //QLabel::setPixmap(newMap);
        scale = ratio;
        resize(ratio * pixmap()->size());
        qDebug() << "Zoom Ratio: " << ratio << "Label Size: " << size();
        break;
    }
    case SELECTING:
        break;
    default:
        break;
    }
}

void QImageLabel::reset() {
    setPixmap(*originalPixmap);
}
