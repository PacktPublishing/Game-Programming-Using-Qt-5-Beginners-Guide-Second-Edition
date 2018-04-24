#include <QCoreApplication>
#include <QSharedMemory>
#include <QTextStream>
#include "../server/gamestats.h"
#include <QDebug>
#include <cstring>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSharedMemory sharedMemory("gameStats");
    if(!sharedMemory.attach(QSharedMemory::ReadOnly)) {
        qDebug() << sharedMemory.errorString() << endl;
        return -1;
    }
    GameStats stats;
    if (!sharedMemory.lock()) {
        qFatal("memory lock failed");
        return -1;
    }
    std::memcpy(&stats, sharedMemory.data(), sizeof(GameStats));
    sharedMemory.unlock();
    qDebug() << "Players online:" << stats.playerCount;
    qDebug() << "Engine up time:" << stats.uptime << "seconds";
    sharedMemory.unlock();
    return 0;
}
