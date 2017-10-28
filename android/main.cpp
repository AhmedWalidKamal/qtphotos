#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <backend.h>
#include <qmlimageprovider.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    QmlImageProvider imgProvider;
//    engine.rootContext()->setContextProperty("imgProvider", imgProvider);


    BackEnd backend;
    engine.rootContext()->setContextProperty("BackEnd", &backend);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
