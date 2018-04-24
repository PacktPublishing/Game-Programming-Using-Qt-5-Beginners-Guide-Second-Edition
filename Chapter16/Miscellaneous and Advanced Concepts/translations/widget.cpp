#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->left, &QPushButton::clicked,
            this, &Widget::leftClicked);
    connect(ui->right, &QPushButton::clicked,
            this, &Widget::rightClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::leftClicked()
{
    QMessageBox::information(this, "", tr("You clicked left!"));
}

void Widget::rightClicked()
{
    QMessageBox::information(this, "", tr("You clicked right!"));
}
