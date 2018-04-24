#include "widget.h"
#include <QMouseEvent>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_selectionStart(-1), m_selectionEnd(-1)
{
}

Widget::~Widget()
{

}

int Widget::selectionStart() const
{
    return m_selectionStart;
}

int Widget::selectionEnd() const
{
    return m_selectionEnd;
}

void Widget::addPoint(unsigned yVal) {
    m_points << qMax(0u, yVal);
    update();
}

void Widget::clear() {
    m_points.clear();
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QRect exposedRect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    QRect r = rect().adjusted(10, 10, -10, -10);
    painter.drawRoundedRect(r, 20, 10);
    painter.save();
    r.adjust(2, 2, -2, -2);
    painter.setViewport(r);
    r.moveTo(0, -r.height() / 2);
    painter.setWindow(r);
    drawSelection(&painter, r, exposedRect);
    drawChart(&painter, r, exposedRect);
    painter.restore();
}

void Widget::drawChart(QPainter *painter, const QRect &rect, const QRect &exposedRect)
{
    painter->setPen(Qt::red);
    painter->drawLine(exposedRect.left(), 0, exposedRect.width(), 0);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    const int lastPoint = qMin(m_points.size(), exposedRect.right() + 1);
    for(int i = exposedRect.left(); i < lastPoint; ++i) {
        if(m_selectionStart <= i && m_selectionEnd >=i) {
            painter->setPen(Qt::white);
        } else {
            painter->setPen(Qt::blue);
        }
        painter->drawLine(i, -m_points.at(i), i, m_points.at(i));
    }
    painter->restore();
    Q_UNUSED(rect)
}

void Widget::mousePressEvent(QMouseEvent *mouseEvent) {
    m_selectionStart = m_selectionEnd = mouseEvent->pos().x() - 12;
    emit selectionChanged();
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *mouseEvent) {
    m_selectionEnd = mouseEvent->pos().x() - 12;
    emit selectionChanged();
    update();
}

void Widget::drawSelection(QPainter *painter, const QRect &rect, const QRect &exposedRect) {
    if(m_selectionStart < 0) {
        return;
    }
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(palette().highlight());
    QRect selectionRect = rect;
    selectionRect.setLeft(m_selectionStart);
    selectionRect.setRight(m_selectionEnd);
    painter->drawRect(selectionRect.intersected(exposedRect));
    painter->restore();
}
