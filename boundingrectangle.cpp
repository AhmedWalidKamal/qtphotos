#include "boundingrectangle.h"

boundingRectangle::boundingRectangle()
{
    rubberBand = NULL;
    rubberBandRect = QRect();
    origin = QPoint();
}

void boundingRectangle::setRectDimensions()
{
    rubberBandRect = rubberBand->geometry().normalized();
}

QRect boundingRectangle::getBoundingRect()
{
    return rubberBandRect;
}

void boundingRectangle::reset()
{
    rubberBand->hide();
    rubberBand = NULL;
    origin = QPoint();
    rubberBandRect = QRect();
}

bool boundingRectangle::isEmpty()
{
    return rubberBand == NULL;
}

bool boundingRectangle::validSize()
{
    return rubberBandRect.size().width() > minimumWidth
            && rubberBandRect.size().height() > minimumHeight;
}

void boundingRectangle::initBoundingRectangle(QPoint initialPoint, QWidget *widget)
{
    origin = initialPoint;
    if (!rubberBand)
        rubberBand = new QRubberBand(QRubberBand::Rectangle, widget);
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
}

void boundingRectangle::updateRectPosition(QPoint newPoint)
{
    if (!rubberBand)
        return;
    rubberBand->setGeometry(QRect(origin, newPoint).normalized());
}

void boundingRectangle::scale(double scaleX, double scaleY) {
    QPoint newTopLeft;
    newTopLeft.setX(rubberBandRect.topLeft().x() * scaleX);
    newTopLeft.setY(rubberBandRect.topLeft().y() * scaleY);
    QPoint newBottomRight;
    newBottomRight.setX(rubberBandRect.bottomRight().x() * scaleX);
    newBottomRight.setY(rubberBandRect.bottomRight().y() * scaleY);
    rubberBandRect.setTopLeft(newTopLeft);
    rubberBandRect.setBottomRight(newBottomRight);
}
