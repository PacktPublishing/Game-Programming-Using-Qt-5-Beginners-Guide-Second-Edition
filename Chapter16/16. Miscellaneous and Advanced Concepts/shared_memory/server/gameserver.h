#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QElapsedTimer>
#include <QObject>
#include <QSharedMemory>
#include <QSlider>



class GameServer : public QObject {
    Q_OBJECT
public:
    GameServer();
    ~GameServer();

private slots:
    void writeState();

private:
    QSharedMemory m_sharedMemory;
    QElapsedTimer m_elapsedTimer;
    QSlider *m_slider;
};

#endif // GAMESERVER_H
