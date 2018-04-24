#include "widget.h"
#include "ui_widget.h"
#include <QNetworkReply>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_networkManager = new QNetworkAccessManager(this);
    m_imageFinishedMapper = new QSignalMapper(this);
    connect(m_imageFinishedMapper, SIGNAL(mapped(QObject*)),
            this, SLOT(imageFinished(QObject*)));
    ui->setupUi(this);
    connect(ui->load, &QPushButton::clicked,
            this, &Widget::load);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::load()
{
    QStringList urls = ui->urls->toPlainText()
            .split("\n", QString::SkipEmptyParts);
    for(const QString& url: urls) {
        QNetworkRequest request(url);
        QNetworkReply *reply = m_networkManager->get(request);
        connect(reply, SIGNAL(finished()),
                m_imageFinishedMapper, SLOT(map()));
        m_imageFinishedMapper->setMapping(reply, reply);
    }
}

void Widget::imageFinished(QObject *replyObject)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(replyObject);
    if (!reply) { return; }
    QString url = reply->url().toString();
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "",
            tr("Failed to load %1: %2").arg(url).arg(reply->errorString()));
    } else {
        QByteArray data = reply->readAll();
        QPixmap pixmap;
        if (!pixmap.loadFromData(data)) {
            QMessageBox::critical(this, "",
                tr("Failed to load pixmap from %1").arg(url));
        } else {
            QLabel *label = new QLabel();
            label->setWindowTitle(url);
            label->setPixmap(pixmap);
            label->show();
        }
    }
    reply->deleteLater();
}
