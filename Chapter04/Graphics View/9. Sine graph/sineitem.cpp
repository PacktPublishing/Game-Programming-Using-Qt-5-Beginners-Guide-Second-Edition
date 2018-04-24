#include "sineitem.h"
#include <QPainter>
#include <math.h>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

SineItem::SineItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    m_maxX = 50;

}

float SineItem::maxX()
{
    return m_maxX;
}

void SineItem::setMaxX(float value)
{
    if (m_maxX == value) {
        return;
    }
    prepareGeometryChange();
    m_maxX = value;
}


QRectF SineItem::boundingRect() const
{
    return QRectF(0, -1, m_maxX, 2);
}

void SineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const qreal detail = QStyleOptionGraphicsItem::levelOfDetailFromTransform(
        painter->worldTransform());
    const qreal dx = 1 / detail;
    QPen pen;
    pen.setCosmetic(true);
    if (option->state & QStyle::State_Selected) {
        pen.setColor(Qt::green);
    }
    painter->setPen(pen);
    const int steps = qRound(m_maxX / dx);
    QPointF previousPoint(0, sin(0));
    for(int i = 1; i < steps; ++i) {
        const float x = dx * i;
        QPointF point(x, sin(x));
        painter->drawLine(previousPoint, point);
        previousPoint = point;
    }
    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void SineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        float x = event->pos().x();
        QPointF point(x, sin(x));
        static const float r = 0.3;
        QGraphicsEllipseItem *ellipse =
                new QGraphicsEllipseItem(-r, -r, 2 * r, 2 * r, this);
        ellipse->setPen(Qt::NoPen);
        ellipse->setBrush(QBrush(Qt::red));
        ellipse->setPos(point);
        event->accept();
    } else {
        event->ignore();
    }
}
