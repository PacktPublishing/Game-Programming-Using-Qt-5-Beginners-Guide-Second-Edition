#include "playerinfo.h"
#include <QMetaEnum>

InventoryItem::Type InventoryItem::typeByName(const QStringRef &r) {
    QMetaEnum metaEnum = QMetaEnum::fromType<InventoryItem::Type>();
    QByteArray latin1 = r.toLatin1();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<InventoryItem::Type>(result);
}
