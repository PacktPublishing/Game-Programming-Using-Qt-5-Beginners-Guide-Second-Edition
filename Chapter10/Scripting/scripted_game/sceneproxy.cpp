#include "sceneproxy.h"
#include "scene.h"
#include "entity.h"
#include "entityproxy.h"

SceneProxy::SceneProxy(Scene *scene) :
    QObject(scene), m_scene(scene)
{

}

QSize SceneProxy::size() const {
    return m_scene->fieldSize();
}

QJSValue SceneProxy::entities() const
{
    QJSValue list = m_scene->jsEngine()->newArray();
    int arrayIndex = 0;
    for(Entity *entity: m_scene->entities()) {
        if (entity->isAlive()) {
            list.setProperty(arrayIndex, entity->proxyValue());
            arrayIndex++;
        }
    }
    return list;
}

