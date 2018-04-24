#ifndef PLAYER_H
#define PLAYER_H

#include <QDataStream>
#include <QPoint>

struct Player {
    QString name;
    qint64 experience;
    QPoint position;
    QChar direction;
};

QDataStream& operator<<(QDataStream &stream, const Player &p);
QDataStream& operator>>(QDataStream &stream, Player &p);

#endif // PLAYER_H
