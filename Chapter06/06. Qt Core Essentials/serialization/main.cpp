#include <QDataStream>
#include <QPoint>
#include <QString>
#include <QBuffer>
#include <QtDebug>
#include "player.h"

int main(int, char**) {
    Player player;
    player.name = "John Doe";
    player.experience = 1234;
    player.position = QPoint(1,2);
    player.direction = 'n';

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    {
        QDataStream stream(&buffer);
        stream << player;
        qDebug() << buffer.data().toHex();
    }

    buffer.close();
    buffer.open(QIODevice::ReadOnly);

    Player restoredPlayer;
    {
        QDataStream stream(&buffer);
        stream >> restoredPlayer;
        qDebug() << restoredPlayer.name << restoredPlayer.experience
                 << restoredPlayer.position << restoredPlayer.direction;
    }

    return 0;
}
