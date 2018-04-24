#include "player.h"

QDataStream& operator<<(QDataStream &stream, const Player &p) {
    stream << p.name;
    stream << p.experience;
    stream << p.position;
    stream << p.direction;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Player &p) {
    stream >> p.name;
    stream >> p.experience;
    stream >> p.position;
    stream >> p.direction;
    return stream;
}
