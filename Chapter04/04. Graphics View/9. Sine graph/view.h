#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // VIEW_H
