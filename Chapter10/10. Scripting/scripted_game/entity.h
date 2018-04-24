#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include <QGraphicsEllipseItem>
#include <QJSValue>

class EntityProxy;
class Scene;

class Entity : public QGraphicsEllipseItem {
public:
    Entity(Scene *scene);



    int team() const;
    void setTeam(int team);

    bool isAlive() const;
    void setAlive(bool isAlive);

    enum { Type = UserType + 1 };
    int type() const;

    EntityProxy *proxy();
    QJSValue proxyValue() const;

private:
    int m_team;
    bool m_alive;
    EntityProxy *m_proxy;
    QJSValue m_proxyValue;


};

#endif // LIVINGENTITY_H
