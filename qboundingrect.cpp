#include "qboundingrect.h"
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QDebug>

QBoundingRectangle::QBoundingRectangle(QWidget *parent): QWidget(parent)
{
    rubberBand = NULL;
    rubberBandRect = QRect();
    origin = QPoint();
    movingOffset = QPoint();
    isMoving = false;
}

void QBoundingRectangle::setupBoundingRect()
{
    rubberBandRect = rubberBand->geometry().normalized();
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
    if (isEmpty()) {
        return;
    }
    rubberBand->hide();
    rubberBand = NULL;
    origin = QPoint();
    rubberBandRect = QRect();
//    rubberBand->setLayout(NULL);
}

bool QBoundingRectangle::isEmpty()
{
    return rubberBand == NULL;
}

bool QBoundingRectangle::validSize()
{
    return rubberBandRect.size().width() > minimumWidth
            && rubberBandRect.size().height() > minimumHeight;
}

bool QBoundingRectangle::contains(QPoint point)
{
    return rubberBand->geometry().contains(point);
}

bool QBoundingRectangle::rubberBandIsMoving()
{
    return isMoving;
}

//void QRubberBand::resizeEvent(QResizeEvent *)
//{
//    QRubberBand.resize(size());
//}

void QBoundingRectangle::resizeEvent(QResizeEvent *) {
    rubberBand->resize(size());
}

void QBoundingRectangle::initBoundingRectangle(QPoint initialPoint, QWidget *widget)
{
    origin = initialPoint;
//    setWindowFlags(Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(rubberBand);
//    this->layout()->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(rubberBand);
    QSizeGrip* grip2 = new QSizeGrip(rubberBand);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
//    qDebug() << rubberBand->layout();
//    this->layout()->addWidget(grip1);
//    this->layout()->addWidget(grip2);
    if (!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle, widget);
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
//    setFocus();
//    show();
}

void QBoundingRectangle::initMoving(QPoint point)
{
    movingOffset = point - rubberBand->pos();
    isMoving = true;
}

void QBoundingRectangle::updateRectPosition(QPoint newPoint)
{
    if (!rubberBand)
        return;
    rubberBand->setGeometry(QRect(origin, newPoint).normalized());
}

void QBoundingRectangle::moveRubberBand(QPoint point)
{
    rubberBand->move(point - movingOffset);
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
