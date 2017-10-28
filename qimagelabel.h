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
    enum State {};
    ~QImageLabel();
    boundingRectangle boundingRect;
    void crop();
    void setPixmap(QPixmap &pixelmap);
    void setPixmap(QPixmap &&pixelmap);

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPixmap *originalPixmap;
    double rotation;
};

#endif // QIMAGELABEL_H
