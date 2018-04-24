#include "playerinfojson.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

PlayerInfoJson::PlayerInfoJson()
{

}

QByteArray PlayerInfoJson::playerInfoToJson(const PlayerInfo &pinfo)
{
    QJsonDocument doc(toJson(pinfo));
    return doc.toJson();
}

QJsonArray PlayerInfoJson::toJson(const PlayerInfo &pinfo) {
    QJsonArray array;
    for(const Player &p: pinfo.players) {
        array << toJson(p);
    }
    return array;
}

QJsonValue PlayerInfoJson::toJson(const Player &player) {
    QJsonObject object;
    object["name"]       = player.name;
    object["password"]   = player.password;
    object["experience"] = player.experience;
    object["hitpoints"]  = player.hitPoints;
    object["location"]   = player.location;
    object["position"]   = QJsonObject({ { "x", player.position.x() },
                                         { "y", player.position.y() } });
    object["inventory"]  = toJson(player.inventory);
    return object;
}

QJsonValue PlayerInfoJson::toJson(const QVector<InventoryItem> &items) {
    QJsonArray array;
    for(const InventoryItem &item: items) {
        array << toJson(item);
    }
    return array;
}

QJsonValue PlayerInfoJson::toJson(const InventoryItem &item) {
    QJsonObject object;
    object["type"] = InventoryItem::typeToName(item.type);
    object["subtype"] = item.subType;
    object["durability"] = item.durability;
    return object;
}



PlayerInfo PlayerInfoJson::playerInfoFromJson(const QByteArray &ba) {
    QJsonDocument doc = QJsonDocument::fromJson(ba);
    if(!doc.isArray()) {
        return PlayerInfo();
    }
    QJsonArray array = doc.array();
    PlayerInfo pinfo;
    for(const QJsonValue &value: array) {
        pinfo.players << playerFromJson(value.toObject());
    }
    return pinfo;
}

Player PlayerInfoJson::playerFromJson(const QJsonObject &object) {
  Player player;
  player.name = object["name"].toString();
  player.password = object["password"].toString();
  player.experience = object["experience"].toDouble();
  player.hitPoints = object["hitpoints"].toDouble();
  player.location = object["location"].toString();
  QJsonObject positionObject = object["position"].toObject();
  player.position = QPoint(positionObject["x"].toInt(),
                           positionObject["y"].toInt());
  player.inventory = inventoryFromJson(object["inventory"].toArray());
  return player;
}

QVector<InventoryItem> PlayerInfoJson::inventoryFromJson(const QJsonArray &array) {
  QVector<InventoryItem> inventory;
  for(const QJsonValue &value: array) {
      inventory << inventoryItemFromJson(value.toObject());
  }
  return inventory;
}

InventoryItem PlayerInfoJson::inventoryItemFromJson(const QJsonObject &object) {
  InventoryItem item;
  item.type = InventoryItem::typeByName(object["type"].toString());
  item.subType = object["subtype"].toString();
  item.durability = object["durability"].toDouble();
  return item;
}
