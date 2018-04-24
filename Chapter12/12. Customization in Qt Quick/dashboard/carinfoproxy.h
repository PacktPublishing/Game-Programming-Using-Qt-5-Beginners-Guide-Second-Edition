#ifndef CARINFOPROXY_H
#define CARINFOPROXY_H

#include "carinfo.h"

class CarInfoProxy : public QObject {
    Q_OBJECT
    Q_PROPERTY(CarInfoEngine *engine READ engine NOTIFY engineChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
public:
    CarInfoProxy(QObject *parent = 0);
    CarInfoEngine *engine() const;
    bool visible() const;
    void setVisible(bool v);
    int speed() const;
    void setSpeed(int v);
    double distance() const;
    void setDistance(double d);
signals:
    void engineChanged();
    void visibleChanged(bool);
    void speedChanged(int);
    void distanceChanged(double);
private:
    CarInfo m_car;
};

#endif // CARINFOPROXY_H
