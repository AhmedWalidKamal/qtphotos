#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H
#include "boundingrectangle.h"
#include <QPixmap>
#include <QLabel>

class QImageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QImageLabel(QWidget *parent = 0);
    enum State {idle, active, selecting};
    ~QImageLabel();
    void crop();
    void setPixmap(QPixmap &pixelmap);
    void setPixmap(QPixmap &&pixelmap);
    State getState();
    void setState(State state);
    void resetBoundingRectangle();

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap *originalPixmap;
    boundingRectangle boundingRect;
    double curRotation;
    double rotationDiff;
    State currState;
};

#endif // QIMAGELABEL_H
