#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QJSValueIterator>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    connect(ui->actionNewDocument, &QAction::triggered,
            this, &MainWindow::newDocument);
    connect(ui->actionOpenDocument, &QAction::triggered,
            this, &MainWindow::openDocument);
    connect(ui->actionSaveDocument, &QAction::triggered,
            this, &MainWindow::saveDocument);
    connect(ui->actionSaveDocumentAs, &QAction::triggered,
            this, &MainWindow::saveDocumentAs);
    connect(ui->actionQuit, &QAction::triggered,
            qApp, &QApplication::quit);
    connect(ui->actionExecuteScript, &QAction::triggered,
            this, &MainWindow::run);

    m_engine.installExtensions(QJSEngine::ConsoleExtension);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newDocument()
{
    setWindowFilePath(QString());
    ui->codeEditor->clear();
    ui->logWindow->clear();
}

void MainWindow::openDocument()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Document"),
        QDir::homePath(), tr("JavaScript Documents (*.js)"));
    if(filePath.isEmpty()) {
        return;
    }
    open(filePath);
}

void MainWindow::saveDocument()
{
    if(windowFilePath().isEmpty()) {
        saveDocumentAs();
        return;
    }
    save(windowFilePath());
}

void MainWindow::saveDocumentAs()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("Save Document"),
        QDir::homePath(), tr("JavaScript Documents (*.js)"));
    if(filePath.isEmpty()) return;
    setWindowFilePath(filePath);
    saveDocument();
}

void MainWindow::open(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Can't open file."));
        return;
    }
    setWindowFilePath(filePath);
    ui->codeEditor->setPlainText(QString::fromUtf8(file.readAll()));
    ui->logWindow->clear();
}

void MainWindow::save(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text)) {
        return;
    }
    file.write(ui->codeEditor->toPlainText().toUtf8());
    ui->codeEditor->document()->setModified(false);
}

void MainWindow::run()
{
    ui->logWindow->clear();
    QTextCursor logCursor = ui->logWindow->textCursor();
    QString scriptSourceCode = ui->codeEditor->toPlainText();    
    QJSValue result = m_engine.evaluate(scriptSourceCode, windowFilePath());
    if(result.isError()) {
        QTextCharFormat errFormat;
        errFormat.setForeground(Qt::red);
        logCursor.insertText(tr("Exception at line %1:\n")
            .arg(result.property("lineNumber").toInt()), errFormat);
        logCursor.insertText(result.toString(), errFormat);
        logCursor.insertBlock();
        logCursor.insertText(result.property("stack").toString(), errFormat);
    } else {
        QTextCharFormat resultFormat;
        resultFormat.setForeground(Qt::blue);
        logCursor.insertText(result.toString(), resultFormat);
    }
}
