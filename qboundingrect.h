#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include <QPoint>
#include <QRubberBand>



class QBoundingRectangle : public QRubberBand
{
public:
    QBoundingRectangle(QWidget *parent);

    void initBoundingRectangle(QPoint initialPoint, QWidget *widget);
    void initMoving(QPoint point);
    void updateRectPosition(QPoint newPoint);
    void moveRubberBand(QPoint point);
    void setupBoundingRect();
    void stopMoving();
    QRect getBoundingRect();
    void scale(double scaleX, double scaleY);
    void reset();
    bool validSize();
    bool contains(QPoint point);
    bool rubberBandIsMoving();
    void resizeEvent(QResizeEvent *);
private:
    QPoint origin;
    QRect rubberBandRect;
    const int minimumWidth = 10;
    const int minimumHeight = 10;
    bool isMoving;
    QPoint movingOffset;

//    void resizeEvent(QResizeEvent *);
};

#endif // BOUNDINGRECTANGLE_H
