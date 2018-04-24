#include <Python.h>
#include "qtpython.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QtPython python;
    python.run("print('Hello from Python')");
    return 0;
}
