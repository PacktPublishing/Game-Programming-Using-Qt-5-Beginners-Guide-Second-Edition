#ifndef QTPYTHON_H
#define QTPYTHON_H

#include <QObject>
#include <QString>
#include <QVector>
#include "qtpythonvalue.h"

class QtPython : public QObject {
    Q_OBJECT
public:
    QtPython(QObject *parent = 0);
    ~QtPython();
    void run(const QString &program);
    QtPythonValue run(const QString &program, const QtPythonValue &globals, const QtPythonValue &locals);

    QtPythonValue import(const QString &name) const;
    QtPythonValue addModule(const QString &name) const;
    QtPythonValue dictionary(const QtPythonValue &module) const;

private:
    QVector<wchar_t> programNameBuffer;
};
#endif // QTPYTHON_H
