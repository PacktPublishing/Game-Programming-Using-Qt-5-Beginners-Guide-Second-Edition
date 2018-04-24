#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QSignalMapper>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private:
  Ui::Widget *ui;
  QNetworkAccessManager *m_networkManager;
  QSignalMapper *m_imageFinishedMapper;


private slots:
  void load();
  void imageFinished(QObject *replyObject);
};

#endif // WIDGET_H
