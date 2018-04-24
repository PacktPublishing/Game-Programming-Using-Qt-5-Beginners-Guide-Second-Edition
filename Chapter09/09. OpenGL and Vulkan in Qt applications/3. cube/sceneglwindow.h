#ifndef SCENEGLWINDOW_H
#define SCENEGLWINDOW_H

#include <QObject>
#include <QOpenGLWindow>

class AbstractGLScene;
class SceneGLWindow : public QOpenGLWindow
{
public:
    SceneGLWindow(QWindow *parent = 0);
    AbstractGLScene* scene() const {
        return m_scene;
    }
    void setScene(AbstractGLScene *s);

protected:
    void initializeGL();
    void paintGL();
private:
    AbstractGLScene *m_scene = nullptr;
};

#endif // SCENEGLWINDOW_H
