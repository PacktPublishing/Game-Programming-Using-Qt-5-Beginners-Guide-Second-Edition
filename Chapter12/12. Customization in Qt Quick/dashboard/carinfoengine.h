#ifndef CARINFOENGINE_H
#define CARINFOENGINE_H

#include <QObject>

class CarInfoEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(int gear READ gear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY rpmChanged)
public:
    CarInfoEngine(QObject *parent = 0);
    int gear() const;
    int rpm() const;

public slots:
    void setGear(int g);
    void setRpm(int arg);

signals:
    void gearChanged(int);
    void rpmChanged(int arg);

private:
    int m_gear;
    int m_rpm;
};

#endif // CARINFOENGINE_H
