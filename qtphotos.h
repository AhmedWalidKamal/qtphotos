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

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actioncopy_triggered();

    void on_actionAbout_triggered();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
    void on_actionCrop_triggered();

    void on_actionSelect_triggered();

private:
    Ui::QtPhotos *ui;
    QImage image;
    QString fileName;

    void display(QImage &imageToDisplay);
    void saveImage(QImage &imageToSave, QString &imageFileName);
    void disableButtonsInitially();
    void enableButtons();
};

#endif // QTPHOTOS_H
