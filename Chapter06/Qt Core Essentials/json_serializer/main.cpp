#include "playerinfojson.h"
#include <QtDebug>
#include <iostream>

QVariant inventoryItemToVariant(const InventoryItem &item) {
    QVariantMap map;
    map["type"] = InventoryItem::typeToName(item.type);
    map["subtype"] = item.subType;
    map["durability"] = item.durability;
    return map;
}

int main(int, char**) {
    PlayerInfo playerInfo;
    Player player;
    player.name = "Gandalf";
    player.password = "mithrandir";
    player.experience = 23456;
    player.hitPoints = 40;
    player.location = "room1";
    player.position = QPoint(1,0);

    InventoryItem item;
    item.type = InventoryItem::Type::Weapon;
    item.durability = 3;
    item.subType = "Long sword";

    qDebug() << inventoryItemToVariant(item);

    player.inventory << item;
    item.type = InventoryItem::Type::Armor;
    item.durability = 10;
    item.subType = "Chain mail";
    playerInfo.players << player;
    QByteArray result = PlayerInfoJson::playerInfoToJson(playerInfo);

    qDebug() << result.constData();

    PlayerInfo playerInfo2 = PlayerInfoJson::playerInfoFromJson(result);
    if(!playerInfo2.players.isEmpty()) {
        qDebug() << playerInfo2.players.first().name;
        qDebug() << playerInfo2.players.first().inventory.first().type;
    }

    return 0;
}
