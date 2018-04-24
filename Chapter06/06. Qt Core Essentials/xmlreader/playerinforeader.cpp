#include "playerinforeader.h"
#include <QtDebug>
#include <QMetaEnum>

PlayerInfoReader::PlayerInfoReader(QIODevice *device) {
    reader.setDevice(device);
}

PlayerInfoReader::Token PlayerInfoReader::tokenByName(const QStringRef &r) {
    QMetaEnum metaEnum = QMetaEnum::fromType<PlayerInfoReader::Token>();
    QByteArray latin1 = r.toLatin1();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<PlayerInfoReader::Token>(result);
}

PlayerInfo PlayerInfoReader::read() {
    if(!reader.readNextStartElement()) {
        return PlayerInfo();
    }
    if (tokenByName(reader.name()) != Token::PlayerInfo) {
        return PlayerInfo();
    }
    PlayerInfo info;
    while(reader.readNextStartElement()) {
        if(tokenByName(reader.name()) == Token::Player) {
            Player p = readPlayer();
            info.players.append(p);
        } else {
            reader.skipCurrentElement();
        }
    }
    return info;
}

Player PlayerInfoReader::readPlayer() {
    Player p;
    const QXmlStreamAttributes& playerAttrs = reader.attributes();
    p.hitPoints = playerAttrs.value("hp").toString().toInt();
    p.experience = playerAttrs.value("exp").toString().toInt();
    while(reader.readNextStartElement()) {
        Token t = tokenByName(reader.name());
        switch(t) {
        case Token::Name:
            p.name = reader.readElementText();
            break;
        case Token::Password:
            p.password = reader.readElementText();
            break;
        case Token::Inventory:
            p.inventory = readInventory();
            break;
        case Token::Location:
            p.location = reader.attributes().value("name").toString();
            while(reader.readNextStartElement()) {
                if(tokenByName(reader.name()) == Token::Position) {
                    const QXmlStreamAttributes& attrs = reader.attributes();
                    p.position.setX(attrs.value("x").toString().toInt());
                    p.position.setY(attrs.value("y").toString().toInt());
                    reader.skipCurrentElement();
                } else {
                    reader.skipCurrentElement();
                }
            }
            break;
        default:
            reader.skipCurrentElement();
        }
    }
    return p;
}

QVector<InventoryItem> PlayerInfoReader::readInventory() {
    QVector<InventoryItem> inventory;
    while(reader.readNextStartElement()) {
        if(tokenByName(reader.name()) != Token::InvItem) {
            reader.skipCurrentElement();
            continue;
        }
        InventoryItem item;
        const QXmlStreamAttributes& attrs = reader.attributes();
        item.durability = attrs.value("durability").toString().toInt();
        item.type = InventoryItem::typeByName(attrs.value("type"));
        while(reader.readNextStartElement()) {
            if(reader.name() == "SubType") {
                item.subType = reader.readElementText();
            }
            else {
                reader.skipCurrentElement();
            }
        }
        inventory << item;
    }
    return inventory;
}
