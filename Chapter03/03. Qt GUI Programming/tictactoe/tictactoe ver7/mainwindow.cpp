#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "configurationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startNewGame, &QAction::triggered,
            this, &MainWindow::startNewGame);
    connect(ui->gameBoard, &TicTacToeWidget::currentPlayerChanged,
            this, &MainWindow::updateNameLabels);
    connect(ui->gameBoard, &TicTacToeWidget::gameOver,
            this, &MainWindow::handleGameOver);
    connect(ui->quit, &QAction::triggered,
            qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelBold(QLabel *label, bool isBold)
{
    QFont f = label->font();
    f.setBold(isBold);
    label->setFont(f);
}

void MainWindow::updateNameLabels()
{
    setLabelBold(ui->player1Name,
        ui->gameBoard->currentPlayer() == TicTacToeWidget::Player::Player1);
    setLabelBold(ui->player2Name,
        ui->gameBoard->currentPlayer() == TicTacToeWidget::Player::Player2);

}

void MainWindow::handleGameOver(TicTacToeWidget::Player winner) {
    QString message;
    if(winner == TicTacToeWidget::Player::Draw) {
        message = tr("Game ended with a draw.");
    } else {
        QString winnerName = winner == TicTacToeWidget::Player::Player1 ?
                    ui->player1Name->text() : ui->player2Name->text();
        message = tr("%1 wins").arg(winnerName);
    }
    QMessageBox::information(this, tr("Info"), message);
}


void MainWindow::startNewGame()
{
    ConfigurationDialog dialog(this);
    if(dialog.exec() == QDialog::Rejected) {
        return; // do nothing if dialog rejected
    }
    ui->player1Name->setText(dialog.player1Name());
    ui->player2Name->setText(dialog.player2Name());
    ui->gameBoard->initNewGame();
}
