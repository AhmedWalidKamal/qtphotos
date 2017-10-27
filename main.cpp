#include "qtphotos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtPhotos w;
    w.show();

    return a.exec();
}
