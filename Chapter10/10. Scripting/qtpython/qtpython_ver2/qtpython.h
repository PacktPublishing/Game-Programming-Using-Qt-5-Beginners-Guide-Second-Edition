#ifndef QTPYTHON_H
#define QTPYTHON_H

#include <QObject>
#include <QString>
#include <QVector>

class QtPython : public QObject {
    Q_OBJECT
public:
    QtPython(QObject *parent = 0);
    ~QtPython();
    void run(const QString &program);

private:
    QVector<wchar_t> programNameBuffer;
};
#endif // QTPYTHON_H
