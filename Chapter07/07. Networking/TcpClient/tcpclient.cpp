#include "tcpclient.h"
#include "ui_tcpclient.h"

#include <QtWidgets>
#include <QtNetwork>

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
  , m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->address->setText(QHostAddress(QHostAddress::LocalHost).toString());
    ui->port->setValue(52693);

    ui->text->setFocus();

    connect(m_socket, &QTcpSocket::readyRead,
            this, &TcpClient::readyRead);
    connect(m_socket, &QTcpSocket::connected,
            this, &TcpClient::connectedToServer);
    connect(m_socket, &QTcpSocket::disconnected,
            this, &TcpClient::disconnectByServer);
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_text_returnPressed()
{
    const QString text = ui->text->text().simplified();
    if (text.isEmpty() || m_socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    QString message = QStringLiteral("%1: %2")
            .arg(m_user).arg(ui->text->text());

    QByteArray messageArray = message.toUtf8();
    messageArray.append(23);
    m_socket->write(messageArray);
    ui->text->clear();
}

void TcpClient::readyRead()
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        return;
    }

    m_receivedData.append(m_socket->readAll());
    while(true) {
        int endIndex = m_receivedData.indexOf(23);
        if (endIndex < 0) {
            break;
        }
        QString message = QString::fromUtf8(m_receivedData.left(endIndex));
        m_receivedData.remove(0, endIndex + 1);
        newMessage(message);
    }
}

void TcpClient::on_connect_clicked()
{
    const QString user = ui->user->text().simplified();
    if (user.isEmpty()) {
        ui->chat->appendPlainText(tr("== Unable to connect to server. "
                                     "You must define an user name."));
        return;
    }

    m_user = user;

    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        ui->chat->appendPlainText(tr("== Connecting..."));
        m_socket->connectToHost(ui->address->text(), ui->port->value());
        updateGui(QAbstractSocket::ConnectingState);
    }
}

void TcpClient::connectedToServer()
{
    ui->chat->appendPlainText(tr("== Connected to server."));
    updateGui(QAbstractSocket::ConnectedState);
}

void TcpClient::on_disconnect_clicked()
{
    if (m_socket->state() != QAbstractSocket::ConnectingState) {
        ui->chat->appendPlainText(tr("== Abort connecting."));
    }
    m_socket->abort();
    updateGui(QAbstractSocket::UnconnectedState);
}

void TcpClient::disconnectByServer()
{
    ui->chat->appendPlainText(tr("== Disconnected by server."));
    updateGui(QAbstractSocket::UnconnectedState);
}

void TcpClient::updateGui(QAbstractSocket::SocketState state)
{
    const bool connected = (state == QAbstractSocket::ConnectedState);
    const bool unconnected = (state == QAbstractSocket::UnconnectedState);
    ui->connect->setEnabled(unconnected);
    ui->address->setEnabled(unconnected);
    ui->port->setEnabled(unconnected);
    ui->user->setEnabled(unconnected);

    ui->disconnect->setEnabled(!unconnected);
    ui->chat->setEnabled(connected);
    ui->text->setEnabled(connected);
}

void TcpClient::newMessage(const QString &message)
{
    ui->chat->appendPlainText(message);
}
