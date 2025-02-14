// #include "gameboard.h"
#include "testwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // GameBoard w;
    TestWindow t;
    t.show();
    // w.show();
    return a.exec();
}
