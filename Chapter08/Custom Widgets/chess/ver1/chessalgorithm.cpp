#include "chessalgorithm.h"
#include "chessboard.h"

ChessAlgorithm::ChessAlgorithm(QObject *parent) : QObject(parent), m_board(0)
{

}

ChessBoard *ChessAlgorithm::board() const
{
    return m_board;
}

void ChessAlgorithm::newGame()
{
    setupBoard();
}

void ChessAlgorithm::setupBoard()
{
    setBoard(new ChessBoard(8,8, this));
}

void ChessAlgorithm::setBoard(ChessBoard *board)
{
    if(board == m_board) return;
    if(m_board) delete m_board;
    m_board = board;
    emit boardChanged(m_board);
}

