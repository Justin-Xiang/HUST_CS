#include "Map.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Map w;
    w.resize(1920, 1080);
    w.show();
    return a.exec();
}
