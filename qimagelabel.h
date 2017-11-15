#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H
#include "qboundingrect.h"
#include <QPixmap>
#include <QLabel>

class QImageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QImageLabel(QWidget *parent = 0);
    enum State {IDLE, ACTIVE, SELECTING, ROTATING};
    ~QImageLabel();
    void crop();
    void setPixmap(QPixmap &pixelmap);
    void setPixmap(QPixmap &&pixelmap);
    State getState();
    void setState(State state);
    void resetBoundingRectangle();
    void zoom(double ratio, bool isZoomIn);
    void reset();
    bool isModified();
private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap *resizedPixmap;
    QPixmap *originalPixmap;
    QBoundingRectangle boundingRect;
    double curRotation;
    double rotationDiff;
    double scale;
    State currState;
    bool imageIsModified;
};

#endif // QIMAGELABEL_H
