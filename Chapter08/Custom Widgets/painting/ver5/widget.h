#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int selectionStart READ selectionStart NOTIFY selectionChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd NOTIFY selectionChanged)
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    int selectionStart() const;

    int selectionEnd() const;

public slots:
    void addPoint(unsigned yVal);
    void clear();

signals:
    void selectionChanged();

protected:
    void paintEvent(QPaintEvent *event);
    void drawChart(QPainter *painter, const QRect &rect, const QRect &exposedRect);
    void drawSelection(QPainter *painter, const QRect &rect, const QRect &exposedRect);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);

    QVector<quint16> m_points;
    int m_selectionStart;
    int m_selectionEnd;
};

#endif // WIDGET_H
