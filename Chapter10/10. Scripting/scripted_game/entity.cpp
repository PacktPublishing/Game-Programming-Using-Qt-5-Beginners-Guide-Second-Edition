#include "entity.h"
#include "entityproxy.h"
#include <QPen>
#include <QBrush>
#include "scene.h"
#include <QDebug>

Entity::Entity(Scene *scene)
{
    m_team = -1;
    m_alive = true;
    setRect(-0.4, -0.4, 0.8, 0.8);
    setPen(Qt::NoPen);
    m_proxy = new EntityProxy(this, scene);
    m_proxyValue = scene->jsEngine()->newQObject(m_proxy);
}

int Entity::team() const {
    return m_team;
}

void Entity::setTeam(int team) {
    m_team = team;
    QColor color;
    switch(team) {
    case 0:
        color = Qt::green;
        break;
    case 1:
        color = Qt::red;
        break;
    }
    setBrush(color);
}

bool Entity::isAlive() const
{
    return m_alive;
}

void Entity::setAlive(bool alive)
{
    m_alive = alive;
    setVisible(alive);
    if (!alive) {
        emit m_proxy->killed();
    }
}

int Entity::type() const
{
    return Type;
}

EntityProxy *Entity::proxy()
{
    return m_proxy;
}

QJSValue Entity::proxyValue() const
{
    return m_proxyValue;
}
