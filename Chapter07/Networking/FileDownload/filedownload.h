#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QWidget>

class QNetworkAccessManager;
class QPlainTextEdit;
class QNetworkReply;

class FileDownload : public QWidget
{
    Q_OBJECT

public:
    explicit FileDownload(QWidget *parent = 0);
    virtual ~FileDownload();

private slots:
    void startDownload();
    void downloadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network_manager;
    QPlainTextEdit *m_edit;
};

#endif // FILEDOWNLOAD_H
