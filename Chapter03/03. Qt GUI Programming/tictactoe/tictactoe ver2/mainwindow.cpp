#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startNewGame, &QPushButton::clicked,
            this, &MainWindow::startNewGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame()
{
    ui->player1Name->setText(tr("Alice"));
    ui->player2Name->setText(tr("Bob"));
}
