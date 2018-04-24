#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QtQml>
#include <QGuiApplication>
#include "regularpolygon.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterType<RegularPolygon>("RegularPolygon", 1, 0, "RegularPolygon");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
