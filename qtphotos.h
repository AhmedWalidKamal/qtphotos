#ifndef QTPHOTOS_H
#define QTPHOTOS_H

#include "boundingrectangle.h"

#include <QMainWindow>
#include <QRubberBand>

namespace Ui {
class QtPhotos;
}

class QtPhotos : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtPhotos(QWidget *parent = 0);
    ~QtPhotos();

private slots:
    void on_actionPrint_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actioncopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFont_triggered();

    void on_actionAbout_triggered();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::QtPhotos *ui;
    boundingRectangle boundingRect;
    QImage image;

    void display(QImage imageToDisplay);
};

#endif // QTPHOTOS_H
