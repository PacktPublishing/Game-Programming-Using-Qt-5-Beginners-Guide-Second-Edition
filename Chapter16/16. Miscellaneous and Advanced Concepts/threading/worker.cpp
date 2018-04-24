#include "worker.h"
#include <math.h>
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent)
{

}

Worker::~Worker()
{
    qDebug() << "worker deleted";
}

void Worker::calculate() {
    float x = 0;
    for(int i = 0; i < 100000000; i++) {
        x += sin(i);
    }
    emit finished(x);
}
