#include "gameserver.h"
#include "gamestats.h"
#include <QTimer>
#include <cstring>
#include <QDebug>

GameServer::GameServer() {
m_sharedMemory.setKey("gameStats");
if(!m_sharedMemory.create(sizeof(GameStats))) {
    qFatal("failed to create shared memory");
    return;
}
    m_elapsedTimer.start();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this,  &GameServer::writeState);
    timer->start(1000);

    m_slider = new QSlider();
    connect(m_slider, &QSlider::valueChanged,
            this,     &GameServer::writeState);
    m_slider->show();
}

GameServer::~GameServer() {
    delete m_slider;
}

void GameServer::writeState() {
    GameStats stats;
    stats.playerCount = m_slider->value();
    stats.uptime = m_elapsedTimer.elapsed() / 1000;
    if(!m_sharedMemory.lock()) {
        qFatal("memory lock failed");
        return;
    }
    qDebug() << "writing to shared memory";
    std::memcpy(m_sharedMemory.data(), &stats, sizeof(GameStats));
    m_sharedMemory.unlock();
}
