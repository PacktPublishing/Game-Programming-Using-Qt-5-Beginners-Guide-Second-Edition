#include "abstractglscene.h"
#include <QOpenGLWindow>

AbstractGLScene::AbstractGLScene(QOpenGLWindow *window)
{
    m_window = window;
}

AbstractGLScene::~AbstractGLScene()
{

}

QOpenGLContext *AbstractGLScene::context() {
    return m_window ? m_window->context() : nullptr;
}

const QOpenGLContext *AbstractGLScene::context() const
{
    return m_window ? m_window->context() : nullptr;
}

void AbstractGLScene::initialize()
{
    if (!initializeOpenGLFunctions()) {
        qFatal("initializeOpenGLFunctions failed");
    }
}
