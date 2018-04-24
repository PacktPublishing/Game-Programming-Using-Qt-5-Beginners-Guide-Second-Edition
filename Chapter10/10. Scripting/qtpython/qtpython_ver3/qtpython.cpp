#include <Python.h>
#include "qtpython.h"
#include <QtDebug>
#include <QCoreApplication>

QtPython::QtPython(QObject *parent) : QObject(parent) {
    QStringList args = qApp->arguments();
    if (args.count() > 0) {
        programNameBuffer.resize(args[0].count());
        args[0].toWCharArray(programNameBuffer.data());
        Py_SetProgramName(programNameBuffer.data());
    }
    Py_InitializeEx(0);
}

QtPython::~QtPython() {
    Py_Finalize();
}

void QtPython::run(const QString &program) {
    PyRun_SimpleString(qPrintable(program));
}

QtPythonValue QtPython::run(const QString &program,
    const QtPythonValue &globals, const QtPythonValue &locals)
{
    PyObject *globalsDict = nullptr;
    PyObject *localsDict = nullptr;
    if(PyModule_Check(globals.m_value)) {
        globalsDict = PyModule_GetDict(globals.m_value);
    } else {
        globalsDict = globals.m_value;
    }
    if(PyModule_Check(locals.m_value)) {
        localsDict = PyModule_GetDict(locals.m_value);
    } else {
        localsDict = locals.m_value;
    }
    return QtPythonValue(PyRun_String(qPrintable(program),
                                      Py_file_input, globalsDict, localsDict));
}

QtPythonValue QtPython::import(const QString &name) const
{
    return QtPythonValue(PyImport_ImportModule(qPrintable(name)));
}

QtPythonValue QtPython::addModule(const QString &name) const
{
    PyObject *retVal = PyImport_AddModule(qPrintable(name));
    Py_INCREF(retVal);
    return QtPythonValue(retVal);
}

QtPythonValue QtPython::dictionary(const QtPythonValue &module) const
{
    PyObject *retVal = PyModule_GetDict(module.m_value);
    Py_INCREF(retVal);
    return QtPythonValue(retVal);
}
