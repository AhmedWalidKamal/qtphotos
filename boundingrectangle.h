#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include <QPoint>
#include <QRubberBand>



class boundingRectangle
{
public:
    boundingRectangle();

    void initBoundingRectangle(QPoint initialPoint, QWidget *widget);
    void initMoving(QPoint point);
    void updateRectPosition(QPoint newPoint);
    void moveRubberBand(QPoint point);
    void setRectDimensions();
    void stopMoving();
    QRect getBoundingRect();
    void scale(double scaleX, double scaleY);
    void reset();
    bool isEmpty();
    bool validSize();
    bool contains(QPoint point);
    bool rubberBandIsMoving();

private:
    QPoint origin;
    QRubberBand *rubberBand;
    QRect rubberBandRect;
    const int minimumWidth = 10;
    const int minimumHeight = 10;
    bool isMoving;
    QPoint movingOffset;
};

#endif // BOUNDINGRECTANGLE_H
