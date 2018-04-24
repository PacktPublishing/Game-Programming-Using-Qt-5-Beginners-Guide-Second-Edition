#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "tictactoewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateNameLabels();
    void handleGameOver(TicTacToeWidget::Player winner);
    void startNewGame();

private:
    Ui::MainWindow *ui;
    static void setLabelBold(QLabel *label, bool isBold);
};

#endif // MAINWINDOW_H
