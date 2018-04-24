//#include <Python.h>
#include "qtpythonvalue.h"


QVariant variantFromPyObject(PyObject *pyObject) {
    if(PyLong_Check(pyObject)) {
        return QVariant((int)PyLong_AsLong(pyObject));
    }
    if(PyUnicode_Check(pyObject)) {
        return QString::fromUtf8(PyUnicode_AsUTF8(pyObject));
    }
    if(pyObject == Py_None) {
        return QVariant();
    }
    if(PyTuple_Check(pyObject)) {
        QVariantList list;
        int size = PyTuple_Size(pyObject);
        for(int i=0;i<size;++i) {
            PyObject *subObject = PyTuple_GetItem(pyObject, i);
            list << variantFromPyObject(subObject);
        }
        return list;
    }
    if(PyDict_Check(pyObject)) {
        QVariantMap map;
        PyObject *key = 0, *value = 0;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyObject, &pos, &key, &value)) {
            QVariant keyVar = variantFromPyObject(key);
            map.insert(keyVar.toString(), variantFromPyObject(value));
        }
        return map;
    }
    return QVariant();
}

QtPythonValue::QtPythonValue() {
    incRef(Py_None);
}

QtPythonValue::QtPythonValue(const QtPythonValue &other) {
    incRef(other.m_value);
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

QVariantList QtPythonValue::toList() const {
    return variantFromPyObject(m_value).toList();
}

QVariantMap QtPythonValue::toMap() const {
    return variantFromPyObject(m_value).toMap();
}

bool QtPythonValue::isNone() const {
    return m_value == Py_None;
}

bool QtPythonValue::isCallable() const {
    return PyCallable_Check(m_value);
}

QtPythonValue QtPythonValue::attribute(const QString &name) const {
    return QtPythonValue(PyObject_GetAttrString(m_value, qPrintable(name)));
}

bool QtPythonValue::setAttribute(const QString &name, const QtPythonValue &value) {
    int retVal = PyObject_SetAttrString(m_value, qPrintable(name), value.m_value);
    return retVal != -1;
}

QtPythonValue QtPythonValue::call(const QVariantList &arguments) const {
    return QtPythonValue(
        PyObject_CallObject(m_value, QtPythonValue(arguments).m_value));
}

QtPythonValue QtPythonValue::call(const QStringList &arguments) const {
    return QtPythonValue(
        PyObject_CallObject(m_value, QtPythonValue(arguments).m_value));
}

QtPythonValue QtPythonValue::toText() const {
    return QtPythonValue(PyObject_Str(m_value));
}

QtPythonValue::QtPythonValue(PyObject *ptr) {
    m_value = ptr;
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

QtPythonValue::QtPythonValue(const QString &str) {
    m_value = PyUnicode_FromString(qPrintable(str));
}

QtPythonValue::QtPythonValue(int val) {
    m_value = PyLong_FromLong(val);
}

QtPythonValue::QtPythonValue(const QVariant &variant)
{
    switch(variant.type()) {
    case QVariant::Invalid:
        incRef(Py_None);
        return;
    case QVariant::String:
        m_value = PyUnicode_FromString(qPrintable(variant.toString()));
        return;
    case QVariant::Int:
        m_value = PyLong_FromLong(variant.toInt());
        return;
    case QVariant::LongLong:
        m_value = PyLong_FromLongLong(variant.toLongLong());
        return;
    case QVariant::List: {
        QVariantList list = variant.toList();
        const int listSize = list.size();
        PyObject *tuple = PyTuple_New(listSize);
        for(int i = 0; i < listSize; ++i) {
            PyTuple_SetItem(tuple, i, QtPythonValue(list.at(i)).m_value);
        }
        m_value = tuple;
        return;
    }
    case QVariant::Map: {
        QVariantMap map = variant.toMap();
        PyObject *dict = PyDict_New();
        for(auto iter = map.begin(); iter != map.end(); ++iter) {
            PyDict_SetItemString(dict, qPrintable(iter.key()),
                                 QtPythonValue(iter.value()).m_value);
        }
        m_value = dict;
        return;
    }
    default:
        incRef(Py_None);
        return;
    }
}

QtPythonValue::QtPythonValue(const QStringList &list)
{
    const int listSize = list.size();
    PyObject *tuple = PyTuple_New(listSize);
    for(int i = 0; i < listSize; ++i) {
        PyTuple_SetItem(tuple, i, QtPythonValue(list.at(i)).m_value);
    }
    m_value = tuple;
}

QtPythonValue::~QtPythonValue()
{
    decRef();
}
