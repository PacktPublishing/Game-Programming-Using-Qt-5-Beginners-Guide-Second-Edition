#include "playerinforeader.h"
#include <QCoreApplication>
#include <QFile>
#include <QtDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QFile file(":/playerinfo.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    PlayerInfoReader reader(&file);
    PlayerInfo playerInfo = reader.read();
    if (!playerInfo.players.isEmpty()) {
        qDebug() << "Count:" << playerInfo.players.count();
        qDebug() << "Size of inventory:" <<
                    playerInfo.players.first().inventory.size();
        qDebug() << "Inventory item:"
                 << playerInfo.players.first().inventory[0].type
                 << playerInfo.players.first().inventory[0].subType;
        qDebug() << "Room:" << playerInfo.players.first().location
                 << playerInfo.players.first().position;
    }
    return 0;
}
