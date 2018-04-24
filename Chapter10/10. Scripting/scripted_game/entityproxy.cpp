#include "entityproxy.h"
#include "entity.h"

EntityProxy::EntityProxy(Entity *entity, QObject *parent) :
    QObject(parent), m_entity(entity)
{


}

int EntityProxy::team() const
{
    return m_entity->team();
}

QPoint EntityProxy::pos() const
{
    return m_entity->pos().toPoint();
}
