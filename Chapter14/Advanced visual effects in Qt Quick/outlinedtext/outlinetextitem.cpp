#include "outlinetextitem.h"
#include "outlinetextitemborder.h"
#include <QPainter>

OutlineTextItem::OutlineTextItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    m_border = new OutlineTextItemBorder(this);
    connect(this, &OutlineTextItem::textChanged,
            this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::colorChanged,
            this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::fontFamilyChanged,
            this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::fontPixelSizeChanged,
            this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::widthChanged,
            this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::colorChanged,
            this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::styleChanged,
            this, &OutlineTextItem::updateItem);
    updateItem();
}

void OutlineTextItem::paint(QPainter *painter) {
    if(m_text.isEmpty()) return;
    painter->setPen(m_border->pen());
    painter->setBrush(m_color);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(-m_boundingRect.topLeft());
    painter->drawPath(m_path);
}

OutlineTextItemBorder *OutlineTextItem::border() const {
    return m_border;
}

QPainterPath OutlineTextItem::borderShape(const QPainterPath &path) const
{
    QPainterPathStroker pathStroker;
    pathStroker.setWidth(m_border->width());
    QPainterPath p = pathStroker.createStroke(path);
    p.addPath(path);
    return p;
}

void OutlineTextItem::updateItem() {
    QFont font(m_fontFamily, m_fontPixelSize);
    m_path = QPainterPath();
    m_path.addText(0, 0, font, m_text);
    m_boundingRect = borderShape(m_path).controlPointRect();
    setImplicitWidth(m_boundingRect.width());
    setImplicitHeight(m_boundingRect.height());
    update();
}

