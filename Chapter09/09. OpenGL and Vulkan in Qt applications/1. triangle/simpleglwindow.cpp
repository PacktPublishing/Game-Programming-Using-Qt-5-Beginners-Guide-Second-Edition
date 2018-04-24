#include "simpleglwindow.h"

SimpleGLWindow::SimpleGLWindow(QWindow *parent) :
    QOpenGLWindow(NoPartialUpdate, parent)
{
    QSurfaceFormat fmt = format();
    fmt.setSamples(16);
    setFormat(fmt);
}

void SimpleGLWindow::initializeGL()
{
    if (!initializeOpenGLFunctions()) {
        qFatal("initializeOpenGLFunctions failed");
    }
    glClearColor(1, 1, 1, 0);
}

void SimpleGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1, 0, 0);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0, 1, 0);
        glVertex3f( 1.0f,-1.0f, 0.0f);
        glColor3f(0, 0, 1);
        glVertex3f(-1.0f,-1.0f, 0.0f);
    }
    glEnd();
}
