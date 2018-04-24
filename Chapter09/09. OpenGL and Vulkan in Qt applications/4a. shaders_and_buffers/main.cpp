#include <QGuiApplication>
#include "sceneglwindow.h"
#include "shaderglscene.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    SceneGLWindow window;
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    window.setFormat(fmt);
    ShaderGLScene scene(&window);
    window.setScene(&scene);
    scene.setAngle(30);
    window.resize(600, 600);
    window.show();
    return app.exec();
}
