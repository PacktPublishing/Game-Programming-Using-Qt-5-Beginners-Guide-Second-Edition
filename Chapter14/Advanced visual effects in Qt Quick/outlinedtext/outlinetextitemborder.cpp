#include "outlinetextitemborder.h"
#include <QPen>


OutlineTextItemBorder::OutlineTextItemBorder(QObject *parent) :
    QObject(parent),
    m_width(0),
    m_color(Qt::transparent),
    m_style(Qt::SolidLine)
{

}

int OutlineTextItemBorder::width() const {
    return m_width;
}

QColor OutlineTextItemBorder::color() const {
    return m_color;
}

Qt::PenStyle OutlineTextItemBorder::style() const {
    return m_style;
}

QPen OutlineTextItemBorder::pen() const {
    QPen p;
    p.setColor(m_color);
    p.setWidth(m_width);
    p.setStyle(m_style);
    return p;
}
