#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "advancedcalculator.h"
#include <QDebug>
#include <QQmlComponent>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    engine.globalObject().setProperty("advancedCalculator",
        engine.newQObject(new AdvancedCalculator));

    {
        QQmlComponent component(&engine);
        component.setData(
            "import QtQuick 2.6\n"
            "import QtQuick.Controls 2.2\n"
            "import QtQuick.Window 2.2\n"
            "Window { Button { text: \"C++ button\" } }", QUrl());
        QObject* object = component.create();
        object->setProperty("visible", true);
        QMetaObject::invokeMethod(object, "showMaximized");
    }
    if (engine.rootObjects().count() == 1) {
        QObject *window = engine.rootObjects()[0];
        QObject *resetButton = window->findChild<QObject*>("buttonReset");
        if (resetButton) {
            resetButton->setProperty("highlighted", true);
        } else {
            qDebug() << "button not found";
        }
        QQmlComponent component(&engine);
        component.setData(
            "import QtQuick 2.6\n"
            "import QtQuick.Controls 2.2\n"
            "Button { text: \"C++ button2\" }", QUrl());
        QObject *object = component.create();
        QObject *calculator = window->findChild<QObject*>("calculator");
        object->setProperty("parent", QVariant::fromValue(calculator));

    }


    return app.exec();
}
