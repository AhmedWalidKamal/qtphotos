#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include <QPoint>
#include <QRubberBand>



class boundingRectangle
{
public:
    boundingRectangle();

    void initBoundingRectangle(QPoint initialPoint, QWidget *widget);
    void updateRectPosition(QPoint newPoint);
    void setRectDimensions();
    QRect getBoundingRect();
    void scale(double scaleX, double scaleY);
    void reset();
    bool isEmpty();
    bool validSize();
private:
    QPoint origin;
    QRubberBand *rubberBand;
    QRect rubberBandRect;
    const int minimumWidth = 10;
    const int minimumHeight = 10;
};

#endif // BOUNDINGRECTANGLE_H
