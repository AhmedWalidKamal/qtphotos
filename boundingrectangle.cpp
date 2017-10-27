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
