#include <QGuiApplication>
#include "sceneglwindow.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    SceneGLWindow window;
    window.resize(600, 400);
    window.show();
    return app.exec();
}
