#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsEllipseItem>

class Coin : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)

public:
    explicit Coin(QGraphicsItem *parent = 0);

    enum { Type = UserType + 1 };
    int type() const;

    void explode();

private:
    bool m_explosion;
};

#endif // COIN_H
