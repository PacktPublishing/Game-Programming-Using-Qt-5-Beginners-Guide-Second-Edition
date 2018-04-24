#ifndef PLAYERINFOREADER_H
#define PLAYERINFOREADER_H

#include <QXmlStreamReader>
#include "playerinfo.h"

class PlayerInfoReader {
    Q_GADGET
public:
    PlayerInfoReader(QIODevice *device);

    enum class Token {
        Invalid = -1,
        PlayerInfo, // root tag
        Player,     // in PlayerInfo
        Name, Password, Inventory, Location, // in Player
        Position,   // in Location
        InvItem     // in Inventory
    };
    Q_ENUM(Token)

    static Token tokenByName(const QStringRef &r);
    PlayerInfo read();
protected:
    Player readPlayer();
    QVector<InventoryItem> readInventory();
private:
    QXmlStreamReader reader;
};

#endif // PLAYERINFOREADER_H
