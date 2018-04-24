#ifndef SCENEPROXY_H
#define SCENEPROXY_H

#include <QObject>
#include <QSize>
#include <QJSValue>

class Scene;

class SceneProxy : public QObject
{
    Q_OBJECT
public:
    SceneProxy(Scene *scene);
    Q_INVOKABLE QSize size() const;
    Q_INVOKABLE QJSValue entities() const;



private:
    Scene *m_scene;

};

#endif // SCENEPROXY_H
