#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <backend.h>
#include "pixmapprovider.h"
#include "pixmap.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    BackEnd backend;
    engine.rootContext()->setContextProperty("BackEnd", &backend);


    engine.addImageProvider("pixmap", new PixmapProvider);
    qmlRegisterType<Pixmap>("com.qPhotosAndroid.types", 1, 0, "Pixmap");

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
