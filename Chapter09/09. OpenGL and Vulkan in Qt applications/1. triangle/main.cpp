#include <QGuiApplication>
#include "simpleglwindow.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    SimpleGLWindow window;
    window.resize(600, 400);
    window.show();
    return app.exec();
}
