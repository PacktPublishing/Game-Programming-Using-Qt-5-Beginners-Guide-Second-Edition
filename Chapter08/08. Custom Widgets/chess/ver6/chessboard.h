#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVector>

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks = 8, int columns = 8, QObject *parent = 0);

    int ranks() const { return m_ranks; }
    int columns() const { return m_columns; }
    char data(int column, int rank) const;
    void setData(int column, int rank, char value);
    void movePiece(int fromColumn, int fromRank, int toColumn, int toRank);
    void setFen(const QString &fen);

protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    void initBoard();
    bool setDataInternal(int column, int rank, char value);

signals:
    void ranksChanged(int);
    void columnsChanged(int);
    void boardReset();
    void dataChanged(int c, int r);

private:
    int m_ranks, m_columns;
    QVector<char> m_boardData;
};

#endif // CHESSBOARD_H
