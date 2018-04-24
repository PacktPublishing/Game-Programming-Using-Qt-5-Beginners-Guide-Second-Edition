#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendRequest();
    void finished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_network_manager;
    QNetworkReply *m_reply;
};

#endif // MAINWINDOW_H
