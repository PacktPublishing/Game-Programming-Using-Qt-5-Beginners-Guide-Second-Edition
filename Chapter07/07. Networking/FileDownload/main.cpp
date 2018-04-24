#include "filedownload.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileDownload w;
    w.show();
    return a.exec();
}
