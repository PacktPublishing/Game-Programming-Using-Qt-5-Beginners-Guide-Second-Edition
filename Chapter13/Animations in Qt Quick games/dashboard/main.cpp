#include <QtWidgets>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QtQml>
#include "ui_form.h"
#include "carinfoengine.h"
#include "carinfoproxy.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QString msg = QStringLiteral("Objects of type CarInfoEngine cannot be created");
    qmlRegisterUncreatableType<CarInfoEngine>("CarInfo", 1, 0, "CarInfoEngine", msg);
    qmlRegisterType<CarInfoProxy>("CarInfo", 1, 0, "CarInfo");

//    qmlRegisterType<CarInfo>("CarInfo", 1, 0, "CarInfo");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
      return -1;
    return app.exec();
}
