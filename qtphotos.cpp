#include "boundingrectangle.h"
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
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

QtPhotos::~QtPhotos()
{
    delete ui;
}

void QtPhotos::on_actionNew_triggered()
{

}

void QtPhotos::mousePressEvent(QMouseEvent *event)
{

}

void QtPhotos::mouseMoveEvent(QMouseEvent *event)
{

}

void QtPhotos::mouseReleaseEvent(QMouseEvent *event)
{

}

void QtPhotos::saveImage(QImage &imageToSave, QString &imageFileName)
{
    QImageWriter writer(imageFileName);
    writer.write(imageToSave);
}

void QtPhotos::on_actionOpen_triggered()
{
    QFileDialog dialog(this, tr("Open Image File"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    initImageDialog(dialog, QFileDialog::AcceptOpen);
    int ret = dialog.exec();
    if (ret != QFileDialog::Accepted)
        return;
    for (const QString& fileName : dialog.selectedFiles()) {
        qDebug() << fileName;
        QImageReader reader(fileName);
        reader.setAutoTransform(true);
        image = reader.read();
        if (image.isNull())
            qDebug() << "Failed to open image";
        //image = image.transformed(trans);
        ui->imageLabel->setPixmap(QPixmap::fromImage(image));
//        QPainter painter(ui->imageLabel);
//        painter.drawPixmap(ui->imageLabel->rect(), QPixmap::fromImage(image));
        //ui->imageLabel->adjustSize();
        qDebug() << image.size();
        qDebug() << ui->scrollArea->widget();
        setWindowFilePath(fileName);
        //ui->scrollArea->show();
        Q_ASSERT(ui->imageLabel->pixmap());
    }
}

void QtPhotos::on_actionSave_triggered()
{
    saveImage(image, fileName);
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
    saveImage(image, imageFileName);
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

void QtPhotos::on_actionCut_triggered()
{
    ui->imageLabel->crop();
    //QImage croppedImage = image.copy(ui->imageLabel->boundingRect.getBoundingRect());
    //display(croppedImage);
}

void QtPhotos::display(QImage &imageToDisplay)
{
    //ui->imageLabel->setPixmap(QPixmap::fromImage(imageToDisplay));

    //ui->imageLabel->boundingRect.reset();
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
