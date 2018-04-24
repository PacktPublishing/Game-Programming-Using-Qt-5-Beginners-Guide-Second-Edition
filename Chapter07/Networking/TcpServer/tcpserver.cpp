#include "tcpserver.h"
#include "ui_tcpserver.h"

#include <QtNetwork>
#include <QPlainTextEdit>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
  , m_server(new QTcpServer(this))
{
    ui->setupUi(this);

    if (!m_server->listen(QHostAddress::LocalHost, 52693)) {
        ui->log->setPlainText(tr("Failure while starting server: %1")
                              .arg(m_server->errorString()));
        return;
    }
    connect(m_server, &QTcpServer::newConnection,
            this, &TcpServer::newConnection);
    ui->address->setText(m_server->serverAddress().toString());
    ui->port->setText(QString::number(m_server->serverPort()));
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::newConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        m_clients << socket;
        ui->disconnectClients->setEnabled(true);
        connect(socket, &QTcpSocket::disconnected,
                this, &TcpServer::removeConnection);
        connect(socket, &QTcpSocket::readyRead,
                this, &TcpServer::readyRead);
        ui->log->appendPlainText(tr("* New connection: %1, port %2")
                                 .arg(socket->peerAddress().toString())
                                 .arg(socket->peerPort()));
    }
}

void TcpServer::removeConnection()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        return;
    }
    ui->log->appendPlainText(tr("* Connection removed: %1, port %2")
                             .arg(socket->peerAddress().toString())
                             .arg(socket->peerPort()));
    m_clients.removeOne(socket);
    m_receivedData.remove(socket);
    socket->deleteLater();
    ui->disconnectClients->setEnabled(!m_clients.isEmpty());
}

void TcpServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        return;
    }
    QByteArray &buffer = m_receivedData[socket];
    buffer.append(socket->readAll());
    while(true) {
        int endIndex = buffer.indexOf(23);
        if (endIndex < 0) {
            break;
        }
        QString message = QString::fromUtf8(buffer.left(endIndex));
        buffer.remove(0, endIndex + 1);
        newMessage(socket, message);
    }
}

void TcpServer::on_disconnectClients_clicked()
{
    foreach (QTcpSocket *socket, m_clients) {
        socket->close();
    }
    ui->disconnectClients->setEnabled(false);
}

void TcpServer::newMessage(QTcpSocket *sender, const QString &message)
{
    ui->log->appendPlainText(tr("Sending message: %1").arg(message));
    QByteArray messageArray = message.toUtf8();
    messageArray.append(23);
    for(QTcpSocket *socket: m_clients) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(messageArray);
        }
    }
    Q_UNUSED(sender)
}
