#ifndef PLAYERINFOJSON_H
#define PLAYERINFOJSON_H

#include "playerinfo.h"
#include <QByteArray>
#include <QJsonValue>

class PlayerInfoJson {
public:
  PlayerInfoJson();
  static QByteArray playerInfoToJson(const PlayerInfo &pinfo);
  static PlayerInfo playerInfoFromJson(const QByteArray &ba);

private:
  static QJsonArray toJson(const PlayerInfo &pinfo);
  static QJsonValue toJson(const Player &player);
  static QJsonValue toJson(const QVector<InventoryItem> &items);
  static QJsonValue toJson(const InventoryItem &item);
  static Player playerFromJson(const QJsonObject &object);
  static QVector<InventoryItem> inventoryFromJson(const QJsonArray &array);
  static InventoryItem inventoryItemFromJson(const QJsonObject &object);
};

#endif // PLAYERINFOJSON_H
