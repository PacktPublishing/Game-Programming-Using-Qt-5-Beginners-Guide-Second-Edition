#include <QApplication>
#include <QGuiApplication>
#include <QLabel>
#include <QPropertyAnimation>
#include "sceneglwindow.h"
#include "cubeglscene.h"
#include <QVBoxLayout>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    SceneGLWindow window;
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    window.setFormat(fmt);
    CubeGLScene scene(&window);
    window.setScene(&scene);
    scene.setTexture(QImage(":/texture.jpg"));

    //window.show();

    QPropertyAnimation animation(&scene, "angle");
    animation.setStartValue(0);
    animation.setEndValue(359);
    animation.setDuration(5000);
    animation.setLoopCount(-1);
    animation.start();

    QWidget widget;
    QVBoxLayout* layout = new QVBoxLayout(&widget);
    layout->addWidget(new QLabel("Scene"), 0);
    QWidget* container = QWidget::createWindowContainer(&window, &widget);
    layout->addWidget(container, 1);
    widget.resize(600, 600);
    widget.show();
    return app.exec();
}
