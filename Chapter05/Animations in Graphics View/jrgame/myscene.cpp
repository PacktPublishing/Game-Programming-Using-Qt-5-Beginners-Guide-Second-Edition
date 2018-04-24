#include "myscene.h"

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QPen>

#include <QGraphicsPixmapItem>

#include "player.h"
#include "coin.h"
#include "backgrounditem.h"
#include <QGamepadManager>
#include <QGamepad>
#include <math.h>

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
  , m_velocity(4)
  , m_worldShift(0)
  , m_groundLevel(300)
  , m_minX(0)
  , m_maxX(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(180)
  , m_fieldWidth(1500)
  , m_player(0)
  , m_sky(0)
  , m_trees(0)
  , m_grass(0)
  , m_coins(0)
  , m_horizontalInput(0)
{
    initPlayField();
    m_timer.setInterval(30);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    QList<int> gamepadIds = QGamepadManager::instance()->connectedGamepads();
    if (!gamepadIds.isEmpty()) {
        QGamepad *gamepad = new QGamepad(gamepadIds[0], this);
        connect(gamepad, &QGamepad::axisLeftXChanged,
                this, &MyScene::axisLeftXChanged);
        connect(gamepad, &QGamepad::axisLeftYChanged,
                this, &MyScene::axisLeftYChanged);
    }

}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Right:
        addHorizontalInput(1);
        break;
    case Qt::Key_Left:
        addHorizontalInput(-1);
        break;
    case Qt::Key_Space:
        jump();
        break;
    default:
        break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Right:
        addHorizontalInput(-1);
        break;
    case Qt::Key_Left:
        addHorizontalInput(1);
        break;
        //    case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}



void MyScene::movePlayer()
{
    const int direction = m_player->direction();
    if (0 == direction) {
        return;
    }

    const int dx = direction * m_velocity;
    qreal newX = qBound(m_minX, m_currentX + dx, m_maxX);
    if (newX == m_currentX) {
        return;
    }
    m_currentX = newX;

    const int shiftBorder = 150;
    int rightShiftBorder = width() - shiftBorder;

    const int visiblePlayerPos = m_currentX - m_worldShift;
    const int newWorldShiftRight = visiblePlayerPos - rightShiftBorder;
    if (newWorldShiftRight > 0) {
        m_worldShift += newWorldShiftRight;
    }
    const int newWorldShiftLeft = shiftBorder - visiblePlayerPos;
    if (newWorldShiftLeft > 0) {
        m_worldShift -= newWorldShiftLeft;
    }
    const int maxWorldShift = m_fieldWidth - qRound(width());
    m_worldShift = qBound(0, m_worldShift, maxWorldShift);
    m_player->setX(m_currentX - m_worldShift);

    const qreal ratio = qreal(m_worldShift) / maxWorldShift;
    applyParallax(ratio, m_sky);
    applyParallax(ratio, m_grass);
    applyParallax(ratio, m_trees);
    applyParallax(ratio, m_coins);

    checkColliding();
}

void MyScene::applyParallax(qreal ratio, QGraphicsItem* item) {
    item->setX(-ratio * (item->boundingRect().width() - width()));
}

void MyScene::initPlayField()
{
    setSceneRect(0, 0, 500, 340);

    m_sky = new BackgroundItem(QPixmap(":/sky"));
    addItem(m_sky);

    BackgroundItem *ground = new BackgroundItem(QPixmap(":/ground"));
    addItem(ground);
    ground->setPos(0, m_groundLevel);

    m_trees = new BackgroundItem(QPixmap(":/trees"));
    m_trees->setPos(0, m_groundLevel - m_trees->boundingRect().height());
    addItem(m_trees);

    m_grass = new BackgroundItem(QPixmap(":/grass"));
    m_grass->setPos(0,m_groundLevel - m_grass->boundingRect().height());
    addItem(m_grass);

    m_player = new Player();
    m_minX = m_player->boundingRect().width() * 0.5;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 0.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height() / 2);
    m_currentX = m_minX;
    addItem(m_player);

    // Add some coins
    m_coins = new QGraphicsRectItem(0, 0, m_fieldWidth, m_jumpHeight);
    m_coins->setPen(Qt::NoPen);
    m_coins->setPos(0, m_groundLevel - m_jumpHeight);
    const int xRange = (m_maxX - m_minX) * 0.94;
    for (int i = 0; i < 25; ++i) {
        Coin *c = new Coin(m_coins);
        c->setPos(m_minX + qrand() % xRange, qrand() % m_jumpHeight);
    }
    addItem(m_coins);
}

void MyScene::jump()
{
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
        m_jumpAnimation->start();
    }
}

void MyScene::addHorizontalInput(int input)
{
    m_horizontalInput += input;
    m_player->setDirection(qBound(-1, m_horizontalInput, 1));
    checkTimer();
}

qreal MyScene::jumpFactor() const
{
    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor)
{
    if (m_jumpFactor == jumpFactor) {
        return;
    }

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);

    qreal groundY = (m_groundLevel - m_player->boundingRect().height() / 2);
    qreal y = groundY - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    m_player->setY(y);

    checkColliding();
}

void MyScene::checkTimer()
{
    if (m_player->direction() == 0) {
        m_timer.stop();
    } else if (!m_timer.isActive()) {
        m_timer.start();
    }
}

void MyScene::checkColliding()
{
    for(QGraphicsItem* item: collidingItems(m_player)) {
        if (Coin *c = qgraphicsitem_cast<Coin*>(item)) {
            c->explode();
        }
    }
}

void MyScene::axisLeftXChanged(double value)
{
    int direction;
    if (value > 0) {
        direction = 1;
    } else if (value < 0) {
        direction = -1;
    } else {
        direction = 0;
    }
    m_player->setDirection(direction);
    checkTimer();
}

void MyScene::axisLeftYChanged(double value)
{
    if (value < -0.25) {
        jump();
    }
}
