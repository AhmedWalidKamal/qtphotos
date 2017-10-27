#include <QtAndroidExtras>
#include "backend.h"

QString imgPath;

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{

}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_qtphotos_QtAndroidGallery_QtAndroidGallery_fileSelected(JNIEnv */*env*/,
                                                             jobject /*obj*/,
                                                             jstring results)
{
    imgPath = QAndroidJniObject(results).toString();
}

#ifdef __cplusplus
}
#endif
void BackEnd::openImage() {
    imgPath = "#";

    QAndroidJniObject::callStaticMethod<void>("com/qtphotos/QtAndroidGallery/QtAndroidGallery",
                                                "openAnImage",
                                                "()V");
        while(imgPath == "#")
            qApp->processEvents();

        if(QFile(imgPath).exists())
        {
            qDebug(imgPath.toLatin1());

            QImageReader reader(imgPath);
            reader.setAutoTransform(true);
            QImage image = reader.read();
            if (image.isNull())
                qDebug() << reader.errorString();

//            ui->label->setPixmap(QPixmap::fromImage(image));
//            ui->label->setScaledContents(true);
//            ui->label->adjustSize();
//            ui->label->show();
        }
}
