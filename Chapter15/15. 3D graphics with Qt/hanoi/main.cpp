#include <QGuiApplication>
#include <Qt3DQuickWindow>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Quick::Qt3DQuickWindow window;
    window.setSource(QUrl("qrc:/main.qml"));
    window.show();
    return app.exec();
}
