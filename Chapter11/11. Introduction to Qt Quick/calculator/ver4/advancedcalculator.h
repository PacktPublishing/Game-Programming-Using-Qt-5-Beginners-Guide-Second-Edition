#ifndef ADVANCEDCALCULATOR_H
#define ADVANCEDCALCULATOR_H

#include <QObject>

class AdvancedCalculator : public QObject
{
  Q_OBJECT
public:
  explicit AdvancedCalculator(QObject *parent = nullptr);
  Q_INVOKABLE double factorial(int argument);

signals:

public slots:
};

#endif // ADVANCEDCALCULATOR_H
