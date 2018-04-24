#include "tictactoewidget.h"
#include <QGridLayout>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    for(int row = 0; row < 3; ++row) {
        for(int column = 0; column < 3; ++column) {
            QPushButton *button = new QPushButton(" ");
            gridLayout->addWidget(button, row, column);
            m_board.append(button);
        }
    }
}
