#include "carinfoproxy.h"

CarInfoProxy::CarInfoProxy(QObject *parent) : QObject(parent) {
    connect(&m_car, &CarInfo::engineChanged,
            this, &CarInfoProxy::engineChanged);
    connect(&m_car, &CarInfo::speedChanged,
            this, &CarInfoProxy::speedChanged);
    connect(&m_car, &CarInfo::distanceChanged,
            this, &CarInfoProxy::distanceChanged);
}

CarInfoEngine *CarInfoProxy::engine() const {
    return m_car.engine();
}

bool CarInfoProxy::visible() const {
    return m_car.isVisible();
}

void CarInfoProxy::setVisible(bool v) {
    if(v == visible()) return;
    m_car.setVisible(v);
    emit visibleChanged(v);
}

int CarInfoProxy::speed() const {
    return m_car.speed();
}

void CarInfoProxy::setSpeed(int v) {
    m_car.setSpeed(v);
}

double CarInfoProxy::distance() const {
    return m_car.distance();
}

void CarInfoProxy::setDistance(double d) {
    m_car.setDistance(d);
}

