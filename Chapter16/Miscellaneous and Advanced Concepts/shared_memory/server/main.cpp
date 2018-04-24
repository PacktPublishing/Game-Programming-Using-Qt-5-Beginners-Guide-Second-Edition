#include <QApplication>
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameServer server;

    return a.exec();
}
