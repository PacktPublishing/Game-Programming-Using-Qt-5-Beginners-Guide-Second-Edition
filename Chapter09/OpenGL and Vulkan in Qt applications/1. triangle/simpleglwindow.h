#ifndef SIMPLEGLWINDOW_H
#define SIMPLEGLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_1_1>

class SimpleGLWindow : public QOpenGLWindow, protected QOpenGLFunctions_1_1
{
public:
    SimpleGLWindow(QWindow *parent = 0);
protected:
    void initializeGL();
    void paintGL();
};

#endif // SIMPLEGLWINDOW_H
