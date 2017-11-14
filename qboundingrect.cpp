#include "qboundingrect.h"
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QDebug>

QBoundingRectangle::QBoundingRectangle(QWidget *parent): QRubberBand(QRubberBand::Rectangle, parent)
{
    rubberBandRect = QRect();
    origin = QPoint();
    movingOffset = QPoint();
    isMoving = false;
}

void QBoundingRectangle::setupBoundingRect()
{
    rubberBandRect = geometry().normalized();
}

void QBoundingRectangle::stopMoving()
{
    isMoving = false;
}

QRect QBoundingRectangle::getBoundingRect()
{
    return rubberBandRect;
}

void QBoundingRectangle::reset()
{
    hide();
}

bool QBoundingRectangle::validSize()
{
    return rubberBandRect.size().width() > minimumWidth
            && rubberBandRect.size().height() > minimumHeight;
}

bool QBoundingRectangle::contains(QPoint point)
{
    return geometry().contains(point);
}

bool QBoundingRectangle::rubberBandIsMoving()
{
    return isMoving;
}

void QBoundingRectangle::resizeEvent(QResizeEvent *) {
    resize(size());
}

void QBoundingRectangle::initBoundingRectangle(QPoint initialPoint)
{
    origin = initialPoint;
//    setWindowFlags(Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
//    qDebug() << rubberBand->layout();
//    this->layout()->addWidget(grip1);
//    this->layout()->addWidget(grip2);
    setGeometry(QRect(origin, QSize()));
    show();
}

void QBoundingRectangle::initMoving(QPoint point)
{
    movingOffset = point - pos();
    isMoving = true;
}

void QBoundingRectangle::updateRectPosition(QPoint newPoint)
{
    setGeometry(QRect(origin, newPoint).normalized());
}

void QBoundingRectangle::moveRubberBand(QPoint point)
{
    move(point - movingOffset);
}

void QBoundingRectangle::scale(double scaleX, double scaleY) {
    QPoint newTopLeft;
    newTopLeft.setX(rubberBandRect.topLeft().x() * scaleX);
    newTopLeft.setY(rubberBandRect.topLeft().y() * scaleY);
    QPoint newBottomRight;
    newBottomRight.setX(rubberBandRect.bottomRight().x() * scaleX);
    newBottomRight.setY(rubberBandRect.bottomRight().y() * scaleY);
    rubberBandRect.setTopLeft(newTopLeft);
    rubberBandRect.setBottomRight(newBottomRight);
}
