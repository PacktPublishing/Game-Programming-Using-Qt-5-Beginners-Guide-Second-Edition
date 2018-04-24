#include "foxandhounds.h"
#include "chessboard.h"
#include <QtDebug>

FoxAndHounds::FoxAndHounds(QObject *parent) : ChessAlgorithm(parent)
{
}

FoxAndHounds::~FoxAndHounds()
{

}

void FoxAndHounds::newGame()
{
    setupBoard();
    board()->setFen("3p4/8/8/8/8/8/8/P1P1P1P1 w"); // 'w' - white to move
    m_fox = QPoint(5,8);
    setResult(NoResult);
    setCurrentPlayer(Player1);
}

bool FoxAndHounds::move(int colFrom, int rankFrom, int colTo, int rankTo)
{
    if(currentPlayer() == NoPlayer) return false;

    // is there a piece of the right color?
    char source = board()->data(colFrom, rankFrom);
    if(currentPlayer() == Player1 && source != 'P') return false;
    if(currentPlayer() == Player2 && source != 'p') return false;

    // both can only move one column right or left
    if(colTo != colFrom+1 && colTo != colFrom-1) return false;

    // do we move within the board?
    if(colTo < 1 || colTo > board()->columns()) return false;
    if(rankTo < 1 || rankTo > board()->ranks()) return false;

    // is the destination field black?
    if((colTo + rankTo) % 2) return false;

    // is the destination field empty?
    char destination = board()->data(colTo, rankTo);
    if(destination != ' ') return false;

    // is white advancing?
    if(currentPlayer() == Player1 && rankTo <= rankFrom) return false;

    board()->movePiece(colFrom, rankFrom, colTo, rankTo); // make the move
    if(currentPlayer() == Player2) {
        m_fox = QPoint(colTo, rankTo); // cache fox position
    }
    // check win condition
    if(currentPlayer() == Player2 && rankTo == 1){
        setResult(Player2Wins); // fox has escaped
    } else if(currentPlayer() == Player1 && !foxCanMove()) {
        setResult(Player1Wins); // fox can't move
    } else {
        // the other player makes the move now
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
    }
    return true;
}

bool FoxAndHounds::foxCanMove() const
{
    if(emptyByOffset(-1, -1) || emptyByOffset(-1, 1) || emptyByOffset(1, -1) || emptyByOffset(1, 1)) return true;
    return false;
}

bool FoxAndHounds::emptyByOffset(int x, int y) const
{
    const int destCol = m_fox.x()+x;
    const int destRank = m_fox.y()+y;
    if(destCol < 1 || destRank < 1 || destCol > board()->columns() || destRank > board()->ranks()) return false;
    return (board()->data(destCol, destRank) == ' ');
}





