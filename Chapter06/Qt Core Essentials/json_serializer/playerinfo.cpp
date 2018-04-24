#include "playerinfo.h"
#include <QMetaEnum>

InventoryItem::Type InventoryItem::typeByName(const QStringRef &r) {
    return typeByName(r.toLatin1());
}

InventoryItem::Type InventoryItem::typeByName(const QString &r)
{
    return typeByName(r.toLatin1());
}

InventoryItem::Type InventoryItem::typeByName(const QByteArray &latin1) {
    QMetaEnum metaEnum = QMetaEnum::fromType<InventoryItem::Type>();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<InventoryItem::Type>(result);
}

const char *InventoryItem::typeToName(InventoryItem::Type value)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<InventoryItem::Type>();
    return metaEnum.valueToKey(static_cast<int>(value));
}
