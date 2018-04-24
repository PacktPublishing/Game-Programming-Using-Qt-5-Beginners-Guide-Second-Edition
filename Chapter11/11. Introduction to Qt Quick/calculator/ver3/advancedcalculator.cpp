#include "advancedcalculator.h"
#include <limits>
AdvancedCalculator::AdvancedCalculator(QObject *parent) : QObject(parent)
{

}

double AdvancedCalculator::factorial(int argument) {
    if (argument < 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (argument > 180) {
      return std::numeric_limits<double>::infinity();
    }
    double r = 1.0;
    for(int i = 2; i <= argument; ++i) {
        r *= i;
    }
    return r;
}
