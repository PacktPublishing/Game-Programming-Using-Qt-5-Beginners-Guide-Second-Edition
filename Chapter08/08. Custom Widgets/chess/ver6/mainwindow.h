#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "chessview.h"
#include "chessalgorithm.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void viewClicked(const QPoint &field);

protected:
    Ui::MainWindow *ui;

private slots:
    void gameOver(ChessAlgorithm::Result);

private:
    ChessView *m_view;
    ChessAlgorithm *m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight *m_selectedField;
};

#endif // MAINWINDOW_H
