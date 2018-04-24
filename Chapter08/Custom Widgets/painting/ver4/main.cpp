#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    for(int i = 0; i < 450; ++i) {
        w.addPoint(qrand() % 120);
    }
    w.show();

    return a.exec();
}
