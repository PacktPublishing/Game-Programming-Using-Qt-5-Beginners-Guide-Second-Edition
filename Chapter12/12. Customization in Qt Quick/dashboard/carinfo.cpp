#include "carinfo.h"
#include "ui_form.h"
#include "carinfoengine.h"

CarInfo::CarInfo() : QWidget(0), ui(new Ui::Form) {
    ui->setupUi(this);
    m_engine = new CarInfoEngine(this);
    m_engine->setGear(ui->gearBox->value());
    m_engine->setRpm(ui->rpmBox->value());
    connect(ui->speedBox, SIGNAL(valueChanged(int)),
            this, SIGNAL(speedChanged(int)));
    connect(ui->distanceBox, SIGNAL(valueChanged(double)),
            this, SIGNAL(distanceChanged(double)));

    connect(ui->distanceSlider, &QSlider::valueChanged,
            ui->distanceBox, &QDoubleSpinBox::setValue);
    connect(this, &CarInfo::distanceChanged,
            ui->distanceSlider, &QSlider::setValue);

    connect(ui->gearBox, SIGNAL(valueChanged(int)),
            m_engine, SLOT(setGear(int)));
    connect(ui->rpmBox, SIGNAL(valueChanged(int)),
            m_engine, SLOT(setRpm(int)));
    connect(m_engine, SIGNAL(gearChanged(int)),
            ui->gearBox, SLOT(setValue(int)));
    connect(m_engine, SIGNAL(rpmChanged(int)),
            ui->rpmBox, SLOT(setValue(int)));
}

int CarInfo::speed() const {
    return ui->speedBox->value();
}
void CarInfo::setSpeed(int s) {
    ui->speedBox->setValue(s);
}
double CarInfo::distance() const {
    return ui->distanceBox->value();
}
void CarInfo::setDistance(double d) {
    ui->distanceBox->setValue(d);
}

CarInfoEngine *CarInfo::engine() const {
    return m_engine;
}

