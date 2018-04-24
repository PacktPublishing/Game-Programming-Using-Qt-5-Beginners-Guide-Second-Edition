#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QIcon>

class ChessBoard;
class ChessView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize fieldSize
               READ fieldSize WRITE setFieldSize
               NOTIFY fieldSizeChanged)
public:
    explicit ChessView(QWidget *parent = 0);
    void setBoard(ChessBoard*);
    ChessBoard* board() const;
    QSize fieldSize() const;
    QSize sizeHint() const;
    QRect fieldRect(int column, int rank) const;
    void setPiece(char type, const QIcon &icon);
    QIcon piece(char type) const;

public slots:
    void setFieldSize(QSize fieldSize);

signals:
    void fieldSizeChanged(QSize fieldSize);

protected:
    void paintEvent(QPaintEvent *event);
    virtual void drawColumn(QPainter *painter, int column);
    virtual void drawRank(QPainter *painter, int rank);
    virtual void drawField(QPainter *painter, int column, int rank);
    virtual void drawPiece(QPainter *painter, int column, int rank);

private:
    QPointer<ChessBoard> m_board;
    QSize m_fieldSize;
    QMap<char,QIcon> m_pieces;
};

#endif // CHESSVIEW_H
