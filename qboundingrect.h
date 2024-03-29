#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include <QPoint>
#include <QRubberBand>



class QBoundingRectangle : public QRubberBand
{
    Q_OBJECT

public:
    QBoundingRectangle(QWidget *parent);
    virtual ~QBoundingRectangle();

    void initBoundingRectangle(QPoint initialPoint, QWidget *widget);
    void updateRectPosition(QPoint newPoint);
    void setupBoundingRect();
    QRect getBoundingRect();
    void scale(double scaleX, double scaleY);
    void reset();
    bool validSize();
    bool contains(QPoint point);
    bool rubberBandIsMoving();

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint origin;
    QRect rubberBandRect;
    const int minimumWidth = 10;
    const int minimumHeight = 10;
    bool isMoving;
    QPoint movingOffset;

    void resizeEvent(QResizeEvent *);
    void fixBounds(QPoint &topLeft);
};

#endif // BOUNDINGRECTANGLE_H
