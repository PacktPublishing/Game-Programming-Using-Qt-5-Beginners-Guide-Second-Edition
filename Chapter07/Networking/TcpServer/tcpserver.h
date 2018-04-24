#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>

namespace Ui {
class TcpServer;
}

class QTcpServer;
class QTcpSocket;

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

private slots:
    void newConnection();
    void removeConnection();
    void readyRead();

    void on_disconnectClients_clicked();

private:
    Ui::TcpServer *ui;
    QTcpServer *m_server;
    QVector<QTcpSocket*> m_clients;
    QHash<QTcpSocket*, QByteArray> m_receivedData;

    void newMessage(QTcpSocket *sender, const QString& message);
};

#endif // TCPSERVER_H
