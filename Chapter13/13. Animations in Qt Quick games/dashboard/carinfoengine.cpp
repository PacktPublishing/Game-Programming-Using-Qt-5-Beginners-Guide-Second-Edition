#include "carinfoengine.h"

CarInfoEngine::CarInfoEngine(QObject *parent) :
    QObject(parent), m_gear(4)
{

}

int CarInfoEngine::gear() const {
    return m_gear;
}

int CarInfoEngine::rpm() const
{
    return m_rpm;
}

void CarInfoEngine::setGear(int g) {
    if(m_gear == g) {
        return;
    }
    m_gear = g;
    emit gearChanged(g);
}

void CarInfoEngine::setRpm(int arg)
{
    if (m_rpm == arg) {
        return;
    }
    m_rpm = arg;
    emit rpmChanged(arg);
}
