#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);
    int direction() const;
    void setDirection(int direction);

private:
    int m_direction;
};

#endif // PLAYER_H
