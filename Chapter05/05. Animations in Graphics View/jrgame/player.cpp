#include "player.h"

#include <QPen>
#include <QDebug>

Player::Player(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , m_direction(0)
{
    QPixmap pixmap(":/elephant");
    setPixmap(pixmap);
    setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
}

int Player::direction() const
{
    return m_direction;
}

void Player::setDirection(int direction)
{
    m_direction = direction;
    if (m_direction != 0) {
        QTransform transform;
        if (m_direction < 0) {
            transform.scale(-1, 1);
        }
        setTransform(transform);
    }
}





