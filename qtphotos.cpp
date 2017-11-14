#include "qboundingrect.h"
#include "qtphotos.h"
#include "ui_qtphotos.h"
#include <QFileDialog>
#include <QImage>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMimeDatabase>
#include <QMimeType>
#include <iostream>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QClipboard>

void initImageDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);

QtPhotos::QtPhotos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtPhotos)
{
    ui->setupUi(this);
    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->imageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->imageLabel->setVisible(false);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidgetResizable(false);
    ui->scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );
    disableButtonsInitially();
    ui->imageLabel->setState(QImageLabel::IDLE);
}

QtPhotos::~QtPhotos()
{
    delete ui;
}

void QtPhotos::saveImage(QString &imageFileName)
{
    QImageWriter writer(imageFileName);
    writer.write(ui->imageLabel->pixmap()->toImage());
}

void QtPhotos::disableButtonsInitially()
{
    ui->actioncopy->setEnabled(false);
    ui->actionCrop->setEnabled(false);
    ui->actionPrint->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionSelect->setEnabled(false);
    ui->actionReset->setEnabled(false);
    ui->actionRotate->setEnabled(false);
    ui->actionZoom_In->setEnabled(false);
    ui->actionZoom_Out->setEnabled(false);
}

void QtPhotos::enableButtons()
{
    ui->actioncopy->setEnabled(true);
    ui->actionPrint->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    ui->actionSelect->setEnabled(true);
    ui->actionRotate->setEnabled(true);
    ui->actionZoom_In->setEnabled(true);
    ui->actionZoom_Out->setEnabled(true);
    ui->actionReset->setEnabled(true);
}

void QtPhotos::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open Image File"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    initImageDialog(dialog, QFileDialog::AcceptOpen);
    int ret = dialog.exec();
    if (ret != QFileDialog::Accepted)
        return;
    fileName = dialog.selectedFiles().first();
    qDebug() << "File Name: " << fileName;
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    QImage image = reader.read();
    if (image.isNull())
        qDebug() << "Failed to open image";
    qDebug() << "Image Size: " << image.size();
    display(QPixmap::fromImage(image));
    setWindowFilePath(fileName);
}

void QtPhotos::on_actionSave_triggered()
{
    saveImage(fileName);
}

void QtPhotos::on_actionSave_as_triggered()
{
    QFileDialog dialog(this, tr("Save Image File"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    initImageDialog(dialog, QFileDialog::AcceptSave);
    int ret = dialog.exec();
    if (ret != QFileDialog::Accepted)
        return;
    for (const QString& str : dialog.selectedFiles()) {
        qDebug() << str;
    }
    QString imageFileName = dialog.selectedFiles().first();
    saveImage(imageFileName);
    fileName = imageFileName;
    setWindowFilePath(fileName);
}

void QtPhotos::on_actionPrint_triggered()
{

}

void QtPhotos::on_actionExit_triggered()
{
    exit(0);
}

void QtPhotos::on_actioncopy_triggered()
{
    #ifndef QT_NO_CLIPBOARD
        QGuiApplication::clipboard()->setPixmap(*ui->imageLabel->pixmap());
    #endif // !QT_NO_CLIPBOARD
}


void QtPhotos::on_actionCrop_triggered()
{
    ui->imageLabel->crop();
}

void QtPhotos::display(QPixmap &pixelMap)
{
    ui->imageLabel->setPixmap(pixelMap);
    enableButtons();
    setCursor(Qt::ArrowCursor);
    ui->actionRotate->setChecked(false);
    ui->actionSelect->setChecked(false);
    curZoom = INITIAL_ZOOM;
    ui->imageLabel->setVisible(true);
}

void QtPhotos::display(QPixmap &&pixelMap) {
    display(pixelMap);
}

void QtPhotos::on_actionAbout_triggered()
{

}

void initImageDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QByteArrayList supportedMimeTypes;
    QStringList mimeTypeFilters;
    QString defaultFilter;
    if (acceptMode == QFileDialog::AcceptOpen) {
        supportedMimeTypes = QImageReader::supportedMimeTypes();
        QMimeDatabase mimeDB;
        QStringList allSupportedFormats;
        for(const QString& mimeTypeFilter: supportedMimeTypes) {
            QMimeType mimeType = mimeDB.mimeTypeForName(mimeTypeFilter);
            if(mimeType.isValid()) {
                allSupportedFormats.append(mimeType.globPatterns());
            }
        }
        defaultFilter = QString("All supported formats (%1)").arg(allSupportedFormats.join(' '));
    } else {
        supportedMimeTypes = QImageWriter::supportedMimeTypes();
        defaultFilter = QString("image/jpeg");
    }

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort(Qt::CaseInsensitive);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    if (acceptMode == QFileDialog::AcceptOpen) {
        QStringList nameFilters = dialog.nameFilters();
        nameFilters.append(defaultFilter);
        dialog.setNameFilters(nameFilters);
        dialog.selectNameFilter(defaultFilter);
    } else {
        dialog.selectMimeTypeFilter(defaultFilter);
        dialog.setDefaultSuffix("jpg");
    }
}

void QtPhotos::on_actionReset_triggered()
{
    setCursor(Qt::ArrowCursor);
    ui->actionRotate->setChecked(false);
    ui->actionSelect->setChecked(false);
    curZoom = INITIAL_ZOOM;
    ui->imageLabel->reset();
}

void QtPhotos::on_actionRotate_toggled(bool active)
{
    if (!active) {
        ui->imageLabel->setState(QImageLabel::ACTIVE);
        setCursor(Qt::ArrowCursor);
    } else {
        ui->actionSelect->setChecked(false);
        ui->imageLabel->setState(QImageLabel::ROTATING);
        QImageReader reader(":/icons/rotate_cursor.png");
        QCursor cursor(QPixmap::fromImage(reader.read()));
        setCursor(cursor);
    }
}

void QtPhotos::on_actionSelect_toggled(bool active)
{
    if (!active) {
        ui->imageLabel->setState(QImageLabel::ACTIVE);
        ui->imageLabel->resetBoundingRectangle();
        setCursor(Qt::ArrowCursor);
        ui->actionCrop->setEnabled(false);
    } else {
        ui->actionRotate->setChecked(false);
        ui->imageLabel->setState(QImageLabel::SELECTING);
        setCursor(Qt::CrossCursor);
        ui->actionCrop->setEnabled(true);
    }
}

void QtPhotos::on_actionZoom_In_triggered()
{
    if (curZoom == ZOOM_LEVELS_COUNT - 1) {
        return;
    }
    if (ui->imageLabel->getState() == QImageLabel::SELECTING) {

    } else {
        curZoom++;
    }
    ui->imageLabel->zoom(zoomLevel[curZoom], true);

}

void QtPhotos::on_actionZoom_Out_triggered()
{
    if (curZoom == 0) {
        return;
    }
    if (ui->imageLabel->getState() == QImageLabel::SELECTING) {

    } else {
        curZoom--;
    }
    ui->imageLabel->zoom(zoomLevel[curZoom], false);
}

void QtPhotos::on_actionPaste_triggered()
{
    #ifndef QT_NO_CLIPBOARD
        if (QGuiApplication::clipboard()->pixmap().isNull()) {
            return;
        }
        display(QGuiApplication::clipboard()->pixmap());
    #endif
}
