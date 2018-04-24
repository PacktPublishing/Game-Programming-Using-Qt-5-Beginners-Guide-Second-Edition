#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QJSEngine>
#include <QQmlEngine>

class Entity;

class Scene : public QGraphicsScene
{
public:
    Scene();
    void start();

    QSize fieldSize() const;
    void setFieldSize(const QSize &fieldSize);

    void setScript(int team, const QString& script);


    QVector<Entity *> entities() const;

    QJSEngine *jsEngine();

    int teamSize() const;
    void setTeamSize(int teamSize);
    void setStepDuration(int msec);

private:
    QSize m_fieldSize;
    int m_teamSize;
    QVector<Entity*> m_entities;
    QQmlEngine m_jsEngine;
    QJSValue m_sceneProxyValue;
    QHash<int, QJSValue> m_teamScripts;
    QTimer* m_stepTimer;

    bool moveEntity(Entity* entity, QPoint pos);

private slots:
    void step();
};

#endif // SCENE_H
