#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_network_manager(new QNetworkAccessManager(this))
    , m_reply(nullptr)
{
    setWindowTitle(tr("Distance Matrix API"));
    ui->setupUi(this);
    connect(ui->search, &QPushButton::clicked,
            this, &MainWindow::sendRequest);
    connect(m_network_manager, &QNetworkAccessManager::finished,
            this, &MainWindow::finished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    if (m_reply != nullptr && m_reply->isRunning()) {
        m_reply->abort();
    }
    ui->result->clear();

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("sensor"),   QStringLiteral("false"));
    query.addQueryItem(QStringLiteral("language"), QStringLiteral("en"));
    query.addQueryItem(QStringLiteral("units"),    QStringLiteral("metric"));
    query.addQueryItem(QStringLiteral("mode"),     ui->vehicle->currentText());
    query.addQueryItem(QStringLiteral("origins"),  ui->from->text());
    query.addQueryItem(QStringLiteral("destinations"), ui->to->text());

    QUrl url(QStringLiteral(
         "https://maps.googleapis.com/maps/api/distancematrix/json"));
    url.setQuery(query);
    m_reply = m_network_manager->get(QNetworkRequest(url));
}

void MainWindow::finished(QNetworkReply *reply)
{
    if (m_reply != reply) {
        reply->deleteLater();
        return;
    }

    m_reply = nullptr;
    if (reply->error() != QNetworkReply::NoError) {
        ui->result->setPlainText(reply->errorString());
        reply->deleteLater();
        return;
    }

    const QByteArray content = reply->readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    if (!doc.isObject()) {
        ui->result->setPlainText(tr("Error while reading the JSON file."));
        reply->deleteLater();
        return;
    }

    const QJsonObject obj = doc.object();
    const QJsonArray origins = obj.value("origin_addresses").toArray();
    const QJsonArray destinations = obj.value("destination_addresses").toArray();

    QString output;
    for (int i = 0; i < origins.count(); ++i) {
        const QString origin = origins.at(i).toString();
        const QJsonArray row = obj.value("rows").toArray().at(i).toObject()
                .value("elements").toArray();
        for (int j = 0; j < destinations.count(); ++j) {
            output += tr("From: %1\n").arg(origin);
            output += tr("To: %1\n").arg(destinations.at(j).toString());

            // get distance and duration
            const QJsonObject data = row.at(j).toObject();
            const QString status = data.value("status").toString();
            if (status == "OK") {
                output += tr("Distance: %1\n").arg(
                    data.value("distance").toObject().value("text").toString());
                output += tr("Duration: %1\n").arg(
                    data.value("duration").toObject().value("text").toString());
            } else if (status == "NOT_FOUND") {
                output += tr("Origin and/or destination "
                             "of this pairing could not be geocoded.\n");
            } else if (status == "ZERO_RESULTS") {
                output += tr("No route could be found.\n");
            } else {
                output += tr("Unknown error.\n");
            }
            output += QStringLiteral("=").repeated(35) + QStringLiteral("\n");
        }
    }
    ui->result->setPlainText(output);
    reply->deleteLater();
}
