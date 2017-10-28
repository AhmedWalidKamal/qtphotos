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
private:
    QPoint origin;
    QRubberBand *rubberBand;
    QRect rubberBandRect;
};

#endif // BOUNDINGRECTANGLE_H
