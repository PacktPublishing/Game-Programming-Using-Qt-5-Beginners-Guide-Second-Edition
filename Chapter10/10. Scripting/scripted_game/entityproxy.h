#ifndef ENTITYPROXY_H
#define ENTITYPROXY_H

#include <QObject>
#include <QPoint>

class Entity;

class EntityProxy : public QObject
{
    Q_OBJECT
public:
    explicit EntityProxy(Entity *entity, QObject *parent = nullptr);
    Q_INVOKABLE int team() const;
    Q_INVOKABLE QPoint pos() const;

signals:
    void killed();
private:
    Entity *m_entity;
};

#endif // ENTITYPROXY_H
