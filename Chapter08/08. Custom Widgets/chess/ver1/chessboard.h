#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
    Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)
public:
    explicit ChessBoard(int ranks = 8, int columns = 8, QObject *parent = 0);

    int ranks() const { return m_ranks; }
    int columns() const { return m_columns; }

protected:
    void setRanks(int newRanks);
    void setColumns(int newColumns);

signals:
    void ranksChanged(int);
    void columnsChanged(int);

private:
    int m_ranks, m_columns;
};

#endif // CHESSBOARD_H
