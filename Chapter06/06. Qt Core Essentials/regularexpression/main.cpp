#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QtDebug>
#include <QMessageBox>

int getWeight(const QString &input) {
    QRegularExpression regex("\\A([1-9]\\d{0,2})\\s*(mg|g|kg)\\z");
    regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(input);
    if(match.hasMatch()) {
        const QString number = match.captured(1);
        int weight = number.toInt();
        const QString unit = match.captured(2).toLower();
        if (unit == "g") {
            weight *= 1000;
        } else if (unit == "kg") {
            weight *= 1000000 ;
        }
        return weight;
    } else {
        return -1;
    }
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QLineEdit le;
    le.show();
    QObject::connect(&le, &QLineEdit::returnPressed, [&]() {
        int result = getWeight(le.text());
        if(result < 0) {
            QMessageBox::warning(&le,
                QObject::tr("Input"),
                QObject::tr("Input doesn't match the regular expression"));
        } else {
            QMessageBox::information(&le,
                QObject::tr("Input"),
                QObject::tr("Input is interpreted as %1 mg").arg(result));
        }
    });
    return app.exec();
}
