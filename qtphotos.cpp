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

void initImageDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);

QtPhotos::QtPhotos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtPhotos)
{
    ui->setupUi(this);
}

QtPhotos::~QtPhotos()
{
    delete ui;
}

void QtPhotos::on_actionNew_triggered()
{

}

void QtPhotos::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open Image File"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    initImageDialog(dialog, QFileDialog::AcceptOpen);
    dialog.exec();
    for (const QString& fileName : dialog.selectedFiles()) {
        qDebug() << fileName;
        QImageReader reader(fileName);
        reader.setAutoTransform(true);
        QImage image = reader.read();
        if (image.isNull())
            qDebug() << "Failed to open image";
        QLabel* imgDisplayLabel = new QLabel("");
        imgDisplayLabel->setPixmap(QPixmap::fromImage(image));
        imgDisplayLabel->setScaledContents(true);
        imgDisplayLabel->adjustSize();
        ui->scrollArea->setWidget(imgDisplayLabel);
        ui->scrollArea->show();
        Q_ASSERT(imgDisplayLabel->pixmap());
    }
}

void QtPhotos::on_actionSave_triggered()
{

}

void QtPhotos::on_actionSave_as_triggered()
{
    QFileDialog dialog(this, tr("Save Image File"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    initImageDialog(dialog, QFileDialog::AcceptSave);
    dialog.exec();
    for (const QString& str : dialog.selectedFiles()) {
        qDebug() << str;
    }
}

void QtPhotos::on_actionPrint_triggered()
{

}

void QtPhotos::on_actionExit_triggered()
{

}

void QtPhotos::on_actioncopy_triggered()
{

}

void QtPhotos::on_actionCut_triggered()
{

}

void QtPhotos::on_actionPaste_triggered()
{

}

void QtPhotos::on_actionUndo_triggered()
{

}

void QtPhotos::on_actionRedo_triggered()
{

}

void QtPhotos::on_actionFont_triggered()
{

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
