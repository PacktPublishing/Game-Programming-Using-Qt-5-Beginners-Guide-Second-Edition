
#ifndef FOXANDHOUNDS_H
#define FOXANDHOUNDS_H

#include <QObject>
#include "chessalgorithm.h"
#include <QPoint>

class FoxAndHounds : public ChessAlgorithm
{
public:
    FoxAndHounds(QObject *parent = 0);
    ~FoxAndHounds();

    void newGame();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo);
protected:
    bool foxCanMove() const;
    bool emptyByOffset(int x, int y) const;
private:
    QPoint m_fox;
};



#endif // FOXANDHOUNDS_H

