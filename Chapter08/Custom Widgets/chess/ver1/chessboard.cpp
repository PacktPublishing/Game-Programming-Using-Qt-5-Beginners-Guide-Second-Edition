#include "chessboard.h"

ChessBoard::ChessBoard(int ranks, int columns, QObject *parent)
    : QObject(parent), m_ranks(ranks), m_columns(columns)
{

}

void ChessBoard::setRanks(int newRanks)
{
    if(ranks() == newRanks) return;
    m_ranks = newRanks;
    emit ranksChanged(m_ranks);
}

void ChessBoard::setColumns(int newColumns)
{
    if(columns() == newColumns) return;
    m_columns = newColumns;
    emit columnsChanged(m_columns);
}
