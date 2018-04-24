#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QTimer>

class QGraphicsPixmapItem;
class QPropertyAnimation;

class BackgroundItem;
class Player;

class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor
               READ jumpFactor
               WRITE setJumpFactor
               NOTIFY jumpFactorChanged)
public:
    explicit MyScene(QObject *parent = 0);

    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void movePlayer();
    void checkTimer();
    void checkColliding();


    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);


signals:
    void jumpFactorChanged(qreal);

private:
    void initPlayField();
    void jump();

    int m_velocity;
    int m_worldShift;
    qreal m_groundLevel;
    qreal m_minX;
    qreal m_maxX;
    QTimer m_timer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight;
    int m_fieldWidth;
    qreal m_currentX;

    Player* m_player;
    BackgroundItem *m_sky;
    BackgroundItem *m_trees;
    BackgroundItem *m_grass;
    QGraphicsRectItem *m_coins;

    int m_horizontalInput;

    void addHorizontalInput(int input);
    void applyParallax(qreal ratio, QGraphicsItem *item);
};

#endif // MYSCENE_H
