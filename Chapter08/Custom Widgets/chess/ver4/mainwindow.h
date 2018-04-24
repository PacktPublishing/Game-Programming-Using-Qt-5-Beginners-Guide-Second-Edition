#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class ChessView;
class ChessAlgorithm;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    Ui::MainWindow *ui;

private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
};

#endif // MAINWINDOW_H
