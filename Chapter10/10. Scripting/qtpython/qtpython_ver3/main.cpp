#include <QCoreApplication>
#include "qtpython.h"
#include "qtpythonvalue.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QtPython python;

    QtPythonValue mainModule = python.addModule("__main__");
    QtPythonValue dict = python.dictionary(mainModule);
    python.run("foo = (1, 2, 3)", dict, dict);
    python.run("print(foo)", dict, dict);

    QtPythonValue module = python.import("os");
    QtPythonValue chdir = module.attribute("chdir");
    chdir.call(QStringList() << "/home");
    QtPythonValue func = module.attribute("getcwd");
    qDebug() << func.call(QVariantList()).toString();

    return 0;
}
