#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_workerThread = new QThread(this);
    m_workerThread->start();
    m_worker = new Worker();
    m_worker->moveToThread(m_workerThread);
    connect(m_worker, &Worker::finished,
            this, &Widget::workerFinished);

            connect(ui->start, &QPushButton::clicked,
                    this, &Widget::start);

}

Widget::~Widget() {
    m_worker->deleteLater();
    m_workerThread->quit();
    m_workerThread->wait();
    delete ui;

}

void Widget::start()
{
    ui->result->setText(tr("Calculating..."));
    QTimer::singleShot(0, m_worker, &Worker::calculate);
}

void Widget::workerFinished(float result) {
    ui->result->setText(tr("Result: %1").arg(result));
}
