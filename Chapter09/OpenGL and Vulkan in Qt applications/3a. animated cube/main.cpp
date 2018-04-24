#include <QGuiApplication>
#include <QPropertyAnimation>
#include "sceneglwindow.h"
#include "cubeglscene.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    SceneGLWindow window;
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    window.setFormat(fmt);
    CubeGLScene scene(&window);
    window.setScene(&scene);
    scene.setTexture(QImage(":/texture.jpg"));
    window.resize(600, 600);
    window.show();

    QPropertyAnimation animation(&scene, "angle");
    animation.setStartValue(0);
    animation.setEndValue(359);
    animation.setDuration(5000);
    animation.setLoopCount(-1);
    animation.start();
    return app.exec();
}
