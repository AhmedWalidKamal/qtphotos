#include "qboundingrect.h"
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QDebug>
#include <QMouseEvent>
#include <algorithm>

QBoundingRectangle::QBoundingRectangle(QWidget *parent): QRubberBand(QRubberBand::Rectangle, parent)
{
    rubberBandRect = QRect();
    origin = QPoint();
    movingOffset = QPoint();
    isMoving = false;
    setWindowFlags(Qt::SubWindow);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
    setCursor(Qt::DragMoveCursor);
}


QBoundingRectangle::~QBoundingRectangle() {

}

void QBoundingRectangle::setupBoundingRect()
{
    rubberBandRect = geometry().normalized();
}

QRect QBoundingRectangle::getBoundingRect()
{
    return rubberBandRect;
}

void QBoundingRectangle::reset()
{
    hide();
}

void QBoundingRectangle::mousePressEvent(QMouseEvent *event) {
    movingOffset = event->pos();
    isMoving = true;
}

void QBoundingRectangle::mouseMoveEvent(QMouseEvent *event) {
    QPoint topLeft = event->pos() - movingOffset + rubberBandRect.topLeft();
    fixBounds(topLeft);
    move(topLeft);
    rubberBandRect = geometry().normalized();
}

void QBoundingRectangle::mouseReleaseEvent(QMouseEvent *event) {
    isMoving = false;
}


void QBoundingRectangle::resizeEvent(QResizeEvent *) {
    resize(size());
    rubberBandRect = geometry().normalized();
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

void QBoundingRectangle::fixBounds(QPoint &topLeft)
{
    qDebug() << "Before bound fixing: " << topLeft;
    topLeft.setX(std::max(0, topLeft.x()));
    topLeft.setY(std::max(0, topLeft.y()));
    topLeft.setX(std::min(parentWidget()->width() - width(), topLeft.x()));
    topLeft.setY(std::min(parentWidget()->height() - height(), topLeft.y()));
    qDebug() << "After bound fixing: " << topLeft;
}

void QBoundingRectangle::initBoundingRectangle(QPoint initialPoint, QWidget *widget)
{
    origin = initialPoint;
    setGeometry(QRect(origin, QSize()));
    show();
    this->activateWindow();
}

void QBoundingRectangle::updateRectPosition(QPoint newPoint)
{
    setGeometry(QRect(origin, newPoint).normalized());
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
