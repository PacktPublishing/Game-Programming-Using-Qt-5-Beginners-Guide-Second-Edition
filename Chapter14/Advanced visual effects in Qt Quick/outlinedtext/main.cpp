#include <QQuickView>
#include <QGuiApplication>
#include <QtQml>
#include "outlinetextitem.h"
#include "outlinetextitemborder.h"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    qmlRegisterUncreatableType<OutlineTextItemBorder>(
         "OutlineTextItem", 1, 0, "OutlineTextItemBorder", "");
    qmlRegisterType<OutlineTextItem>(
         "OutlineTextItem", 1, 0, "OutlineTextItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
      return -1;

    return app.exec();
}
