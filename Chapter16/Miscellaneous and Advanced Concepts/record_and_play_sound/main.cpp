#include "recordandplaysound.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecordAndPlaySound mainWindow;
    mainWindow.show();
    return a.exec();
}
