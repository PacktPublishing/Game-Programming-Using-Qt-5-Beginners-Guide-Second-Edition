#ifndef CARINFO_H
#define CARINFO_H

#include <QObject>
#include <QWidget>
#include <QDate>

namespace Ui {
class Form;
}

class CarInfoEngine;

class CarInfo : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(CarInfoEngine* engine READ engine NOTIFY engineChanged)
public:
    CarInfo();
    int speed() const;
    void setSpeed(int s);
    double distance() const;
    void setDistance(double d);
    CarInfoEngine* engine() const;

signals:
    void speedChanged(int);
    void distanceChanged(double);
    void engineChanged();
private:
    CarInfoEngine *m_engine;
    Ui::Form *ui;
};




#endif // CARINFO_H
