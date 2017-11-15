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
QString BackEnd::openImage() {

    // label is always null for some reason, try other data types like QObject and stuff.
    imgPath = "#";

    QAndroidJniObject::callStaticMethod<void>("com/qtphotos/QtAndroidGallery/QtAndroidGallery",
                                              "openAnImage",
                                              "()V");
    while(imgPath == "#")
        qApp->processEvents();

    if(QFile(imgPath).exists())
    {
        this->currentImage.load(imgPath);
        return imgPath;
    }
    return NULL;
}