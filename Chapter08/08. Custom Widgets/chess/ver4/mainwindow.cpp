#include "mainwindow.h"
#include "chessview.h"
#include "chessalgorithm.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_view = new ChessView;

    m_view->setPiece('P', QIcon(":/pieces/Chess_plt45.svg")); // pawn
    m_view->setPiece('K', QIcon(":/pieces/Chess_klt45.svg")); // king
    m_view->setPiece('Q', QIcon(":/pieces/Chess_qlt45.svg")); // queen
    m_view->setPiece('R', QIcon(":/pieces/Chess_rlt45.svg")); // rook
    m_view->setPiece('N', QIcon(":/pieces/Chess_nlt45.svg")); // knight
    m_view->setPiece('B', QIcon(":/pieces/Chess_blt45.svg")); // bishop

    m_view->setPiece('p', QIcon(":/pieces/Chess_pdt45.svg")); // pawn
    m_view->setPiece('k', QIcon(":/pieces/Chess_kdt45.svg")); // king
    m_view->setPiece('q', QIcon(":/pieces/Chess_qdt45.svg")); // queen
    m_view->setPiece('r', QIcon(":/pieces/Chess_rdt45.svg")); // rook
    m_view->setPiece('n', QIcon(":/pieces/Chess_ndt45.svg")); // knight
    m_view->setPiece('b', QIcon(":/pieces/Chess_bdt45.svg")); // bishop

    m_algorithm = new ChessAlgorithm(this);
    m_algorithm->newGame();
    m_view->setBoard(m_algorithm->board());
    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(50,50));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

