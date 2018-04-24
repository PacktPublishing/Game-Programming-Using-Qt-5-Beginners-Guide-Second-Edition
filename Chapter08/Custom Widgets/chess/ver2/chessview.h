#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QWidget>
#include <QPointer>

class ChessBoard;
class ChessView : public QWidget
{
    Q_OBJECT
public:
    explicit ChessView(QWidget *parent = 0);
    void setBoard(ChessBoard*);
    ChessBoard* board() const;

private:
    QPointer<ChessBoard> m_board;
};

#endif // CHESSVIEW_H
