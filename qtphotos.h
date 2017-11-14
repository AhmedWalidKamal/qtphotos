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

    void on_actionCrop_triggered();

    void on_actionReset_triggered();

    void on_actionRotate_toggled(bool arg1);

    void on_actionSelect_toggled(bool arg1);

private:
    Ui::QtPhotos *ui;
    QImage image;
    QString fileName;
    double zoomLevel[11] = {0.1, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 2, 2.5, 3, 4};
    void display(QImage &imageToDisplay);
    void saveImage(QString &imageFileName);
    void disableButtonsInitially();
    void enableButtons();
};

#endif // QTPHOTOS_H
