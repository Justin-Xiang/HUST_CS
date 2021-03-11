#include "shudu.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shudu w;
    w.resize(600, 600);
    w.SetQipan();
    //w.RandGener("shudu.txt");
    w.setWindowTitle("CS1906 廖翔 数独游戏");
    w.show();
    return a.exec();
}
