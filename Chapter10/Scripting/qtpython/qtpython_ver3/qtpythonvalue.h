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
    QtPythonValue(const QVariant &variant);
    QtPythonValue(const QStringList &list);
    ~QtPythonValue();

    int toInt() const;
    QString toString() const;
    QVariantList toList() const;
    QVariantMap toMap() const;
    bool isNone() const;
    bool isCallable() const;

    QtPythonValue attribute(const QString &name) const;
    bool setAttribute(const QString &name, const QtPythonValue &value);

    QtPythonValue call(const QVariantList &arguments) const;
    QtPythonValue call(const QStringList &arguments) const;

    QtPythonValue toText() const;

private:
    QtPythonValue(PyObject *ptr);
    void incRef();
    void incRef(PyObject *val);
    void decRef();

    PyObject *m_value;
    friend class QtPython;
};

#endif // QTPYTHONVALUE_H
