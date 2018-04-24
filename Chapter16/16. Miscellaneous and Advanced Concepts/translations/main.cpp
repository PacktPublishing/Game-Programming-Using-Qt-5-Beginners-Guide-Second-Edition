#include "widget.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (!translator.load(QLocale::German, ":/translations/myapp_")) {
        qWarning() << "failed to load translation";
    }
    app.installTranslator(&translator);

    Widget w;
    w.show();

    return app.exec();
}
