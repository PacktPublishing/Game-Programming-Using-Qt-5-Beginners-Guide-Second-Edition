#ifndef QTPYTHONVALUE_H
#define QTPYTHONVALUE_H

#include <Python.h>
#include <QString>
#include <QVariant>


class QtPythonValue {
public:
    QtPythonValue();
    QtPythonValue(const QtPythonValue &other);
    QtPythonValue& operator=(const QtPythonValue &other);

    QtPythonValue(int val);
    QtPythonValue(const QString &str);
    ~QtPythonValue();

    int toInt() const;
    QString toString() const;
    bool isNone() const;

private:
    QtPythonValue(PyObject *ptr);
    void incRef();
    void incRef(PyObject *val);
    void decRef();

    PyObject *m_value;
    friend class QtPython;
};

#endif // QTPYTHONVALUE_H
