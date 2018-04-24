#ifndef OUTILINETEXTITEM_H
#define OUTILINETEXTITEM_H

#include <QQuickPaintedItem>
#include <QPainterPath>

class OutlineTextItemBorder;

class OutlineTextItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text
                            NOTIFY textChanged)
    Q_PROPERTY(QColor color MEMBER m_color
                            NOTIFY colorChanged)
    Q_PROPERTY(OutlineTextItemBorder* border READ border
                            NOTIFY borderChanged)
    Q_PROPERTY(QString fontFamily MEMBER m_fontFamily
                            NOTIFY fontFamilyChanged)
    Q_PROPERTY(int fontPixelSize MEMBER m_fontPixelSize
                            NOTIFY fontPixelSizeChanged)
public:
    OutlineTextItem(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    OutlineTextItemBorder* border() const;
    QPainterPath borderShape(const QPainterPath &path) const;
private slots:
    void updateItem();
signals:
    void textChanged(QString);
    void colorChanged(QColor);
    void borderChanged();
    void fontFamilyChanged(QString);
    void fontPixelSizeChanged(int);
private:
    OutlineTextItemBorder* m_border;
    QPainterPath m_path;
    QRectF m_boundingRect;
    QString m_text;
    QColor m_color;
    QString m_fontFamily;
    int m_fontPixelSize;
};

#endif // OUTILINETEXTITEM_H
