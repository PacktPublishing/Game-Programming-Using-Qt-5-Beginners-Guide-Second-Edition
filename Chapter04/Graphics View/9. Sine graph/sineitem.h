#ifndef SINEITEM_H
#define SINEITEM_H

#include <QGraphicsItem>


class SineItem : public QGraphicsItem
{
public:
    SineItem();
    float maxX();
    void setMaxX(float value);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    float m_maxX;
};

#endif // SINEITEM_H
