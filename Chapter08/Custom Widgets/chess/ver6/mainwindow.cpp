#include "mainwindow.h"
#include "chessboard.h"
#include "chessview.h"
#include "chessalgorithm.h"
#include "foxandhounds.h"
#include <QLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_selectedField(0)
{
    ui->setupUi(this);
    m_view = new ChessView;
    connect(m_view, &ChessView::clicked,
            this, &MainWindow::viewClicked);

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

    m_algorithm = new FoxAndHounds(this);
    m_algorithm->newGame();
    m_view->setBoard(m_algorithm->board());
    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(50,50));
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(m_algorithm, SIGNAL(gameOver(ChessAlgorithm::Result)), this, SLOT(gameOver(ChessAlgorithm::Result)));
}

void MainWindow::viewClicked(const QPoint &field)
{
    if(m_clickPoint.isNull()) {
        if(m_view->board()->data(field.x(), field.y()) != ' ') {
            m_clickPoint = field;
            m_selectedField = new ChessView::FieldHighlight(
                        field.x(), field.y(), QColor(255, 0, 0, 50)
                        );
            m_view->addHighlight(m_selectedField);
        }
    } else {
        if(field != m_clickPoint) {
            m_algorithm->move(m_clickPoint, field);
        }
        m_clickPoint = QPoint();
        m_view->removeHighlight(m_selectedField);
        delete m_selectedField;
        m_selectedField = 0;
    }
}

void MainWindow::gameOver(ChessAlgorithm::Result result)
{
    QString text;
    switch(result) {
    case ChessAlgorithm::Player1Wins: text = "Hounds win!"; break;
    case ChessAlgorithm::Player2Wins: text = "Fox wins!"; break;
    default:
        text = "It's a draw";
    }

    QMessageBox::information(this, "Game over", QStringLiteral("The game has ended. %1").arg(text));
}
