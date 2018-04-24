#include "chessview.h"
#include "chessboard.h"

ChessView::ChessView(QWidget *parent) : QWidget(parent)
{

}

void ChessView::setBoard(ChessBoard *board)
{
    if(m_board == board) return;

    if(m_board) {
        // disconnect all signal-slot connections between m_board and this
        m_board->disconnect(this);
    }
    m_board = board;
    // connect signals (to be done later)
    updateGeometry();
}

ChessBoard *ChessView::ChessView::board() const { return m_board; }

