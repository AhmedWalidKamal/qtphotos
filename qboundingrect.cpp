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
    setWindowFlags(windowFlags() | Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
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

bool QBoundingRectangle::outOfBounds(QPoint topLeft)
{
    qDebug() << "Parent Widget Size: " << parentWidget()->size();
    qDebug() << "Top Left point " << topLeft;
    qDebug() << "height: " << height() << ", width: " << width();
    if (topLeft.x() < 0 || topLeft.y() < 0
            || topLeft.y() + height() > parentWidget()->size().height()
            || topLeft.x() + width() > parentWidget()->size().width()) {
        return true;
    }
    return false;
}

void QBoundingRectangle::initBoundingRectangle(QPoint initialPoint, QWidget *widget)
{
    origin = initialPoint;
    setGeometry(QRect(origin, QSize()));
    show();
    this->activateWindow();
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
    QPoint topLeft = point - movingOffset;
    if (!outOfBounds(topLeft)) {
        move(point - movingOffset);
        rubberBandRect = geometry().normalized();
    }
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
