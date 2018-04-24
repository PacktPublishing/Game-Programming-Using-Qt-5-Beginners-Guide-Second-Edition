#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <QString>
#include <QVector>
#include <QPoint>
#include <QObject>

class InventoryItem {
    Q_GADGET
public:
    enum class Type {
        Weapon,
        Armor,
        Gem,
        Book,
        Other
    };
    Q_ENUM(Type)

    Type type;
    QString subType;
    int durability;

    static Type typeByName(const QStringRef &r);
};

class Player {
public:
    QString name;
    QString password;
    int experience;
    int hitPoints;
    QVector<InventoryItem> inventory;
    QString location;
    QPoint position;
};

struct PlayerInfo {
    QVector<Player> players;
};

#endif // PLAYERDATA_H

