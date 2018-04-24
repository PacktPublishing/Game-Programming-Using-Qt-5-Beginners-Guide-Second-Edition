#include "filedownload.h"

#include <QPlainTextEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>
#include <QNetworkReply>

FileDownload::FileDownload(QWidget *parent)
    : QWidget(parent)
{
    m_network_manager = new QNetworkAccessManager(this);
    m_edit = new QPlainTextEdit;
    m_edit->setReadOnly(true);
    QPushButton *button = new QPushButton(tr("Load File"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_edit);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, &QPushButton::clicked,
            this, &FileDownload::startDownload);
    connect(m_network_manager, &QNetworkAccessManager::finished,
            this, &FileDownload::downloadFinished);
}

FileDownload::~FileDownload()
{

}

void FileDownload::startDownload() {
    QUrl url("https://www.google.com/robots.txt");
    m_network_manager->get(QNetworkRequest(url));
}

void FileDownload::downloadFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        const QString error = reply->errorString();
        m_edit->setPlainText(error);
        return;
    }

    const QByteArray content = reply->readAll();
    m_edit->setPlainText(QString::fromUtf8(content));
    reply->deleteLater();
}
