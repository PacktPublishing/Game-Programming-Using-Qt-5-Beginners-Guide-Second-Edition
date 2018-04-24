#include "qtpythonvalue.h"

QtPythonValue::QtPythonValue() {
    incRef(Py_None);
}

QtPythonValue::QtPythonValue(const QtPythonValue &other) {
    incRef(other.m_value);
}

QtPythonValue::QtPythonValue(PyObject *ptr) {
    m_value = ptr;
}

QtPythonValue::QtPythonValue(const QString &str) {
    m_value = PyUnicode_FromString(qPrintable(str));
}

QtPythonValue::QtPythonValue(int val) {
    m_value = PyLong_FromLong(val);
}

QtPythonValue::~QtPythonValue()
{
    decRef();
}

QtPythonValue &QtPythonValue::operator=(const QtPythonValue &other) {
    if(m_value == other.m_value) {
        return *this;
    }
    decRef();
    incRef(other.m_value);
    return *this;
}

int QtPythonValue::toInt() const {
    return PyLong_Check(m_value) ? PyLong_AsLong(m_value) : 0;
}

QString QtPythonValue::toString() const {
    return PyUnicode_Check(m_value) ?
        QString::fromUtf8(PyUnicode_AsUTF8(m_value)) : QString();
}

bool QtPythonValue::isNone() const {
    return m_value == Py_None;
}


void QtPythonValue::incRef(PyObject *val) {
    m_value = val;
    incRef();
}
void QtPythonValue::incRef() {
    if(m_value) {
        Py_INCREF(m_value);
    }
}
void QtPythonValue::decRef() {
    if(m_value) {
        Py_DECREF(m_value);
    }
}

