#ifndef WIDGET_H
#define WIDGET_H

#include <QThread>
#include <QWidget>
#include "worker.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QThread* m_workerThread;
    Worker* m_worker;

private slots:
    void start();
    void workerFinished(float result);
};


#endif // WIDGET_H
