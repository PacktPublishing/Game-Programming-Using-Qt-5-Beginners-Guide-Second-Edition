#include "scene.h"
#include "entity.h"
#include <QDebug>
#include "sceneproxy.h"
#include <QTimer>

Scene::Scene()
{
    m_teamSize = 0;
    m_jsEngine.installExtensions(QJSEngine::ConsoleExtension);
    SceneProxy *sceneProxy = new SceneProxy(this);
    m_sceneProxyValue = m_jsEngine.newQObject(sceneProxy);

    m_stepTimer = new QTimer(this);
    connect(m_stepTimer, &QTimer::timeout,
            this, &Scene::step);
    m_stepTimer->setInterval(1000);
}

void Scene::start() {
    const int TEAM_COUNT = 2;
    for(int i = 0; i < m_teamSize; i++) {
        for(int team = 0; team < TEAM_COUNT; team++) {
            Entity* entity = new Entity(this);
            entity->setTeam(team);
            QPoint pos;
            do {
                pos.setX(qrand() % m_fieldSize.width());
                pos.setY(qrand() % m_fieldSize.height());
            } while(itemAt(pos, QTransform()));
            entity->setPos(pos);
            addItem(entity);
            m_entities << entity;
        }
    }

    for(int team = 0; team < TEAM_COUNT; team++) {
        QJSValue script = m_teamScripts.value(team);
        if (script.isUndefined()) {
            continue;
        }
        if (!script.hasProperty("init")) {
            continue;
        }
        m_jsEngine.globalObject().setProperty("field", m_sceneProxyValue);
        QJSValue scriptOutput = script.property("init").call();
        if (scriptOutput.isError()) {
            qDebug() << "script error: " << scriptOutput.toString();
            continue;
        }
    }
    m_stepTimer->start();
}

QSize Scene::fieldSize() const
{
    return m_fieldSize;
}

void Scene::setFieldSize(const QSize &fieldSize)
{
    m_fieldSize = fieldSize;
    setSceneRect(-1, -1,
                 m_fieldSize.width() + 2,
                 m_fieldSize.height() + 2);
}

void Scene::setScript(int team, const QString &script) {
    QJSValue value = m_jsEngine.evaluate(script);
    if (value.isError()) {
        qDebug() << "js error: " << value.toString();
        return;
    }
    if(!value.isObject()) {
        qDebug() << "script must return an object";
        return;
    }
    m_teamScripts[team] = value;
}

QVector<Entity *> Scene::entities() const
{
    return m_entities;
}

QJSEngine *Scene::jsEngine()
{
    return &m_jsEngine;
}

int Scene::teamSize() const
{
    return m_teamSize;
}

void Scene::setTeamSize(int teamSize)
{
    m_teamSize = teamSize;
}

void Scene::setStepDuration(int msec)
{
    m_stepTimer->setInterval(msec);
}

bool Scene::moveEntity(Entity *entity, QPoint pos) {
    if (pos.x() < 0 || pos.y() < 0 ||
        pos.x() >= m_fieldSize.width() ||
        pos.y() >= m_fieldSize.height())
    {
        return false; // out of field bounds
    }
    QPoint posChange = entity->pos().toPoint() - pos;
    if (posChange.isNull()) {
        return true; // no change
    }
    if (qAbs(posChange.x()) > 1 || qAbs(posChange.y()) > 1) {
        return false; // invalid move
    }
    QGraphicsItem* item = itemAt(pos, QTransform());
    Entity* otherEntity = qgraphicsitem_cast<Entity*>(item);
    if (otherEntity) {
        otherEntity->setAlive(false);
    }
    entity->setPos(pos);
    return true;
}

void Scene::step() {
    for(Entity* entity: m_entities) {
        if (!entity->isAlive()) {
            continue;
        }
        QJSValue script = m_teamScripts.value(entity->team());
        if (script.isUndefined()) {
            continue;
        }
        m_jsEngine.globalObject().setProperty("field", m_sceneProxyValue);

        QJSValue scriptOutput =
            script.property("step").call({ entity->proxyValue() });
        if (scriptOutput.isError()) {
            qDebug() << "script error: " << scriptOutput.toString();
            continue;
        }
        QJSValue scriptOutputX = scriptOutput.property("x");
        QJSValue scriptOutputY = scriptOutput.property("y");
        if (!scriptOutputX.isNumber() || !scriptOutputY.isNumber()) {
            qDebug() << "invalid script output: " << scriptOutput.toVariant();
            continue;
        }
        QPoint pos(scriptOutputX.toInt(), scriptOutputY.toInt());
        if (!moveEntity(entity, pos)) {
            qDebug() << "invalid move";
        }
    }
}
