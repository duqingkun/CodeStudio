#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qsciapis.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QsciScintilla *coder = new QsciScintilla(this);
    this->setCentralWidget(coder);

    QsciLexerCSharp *csharp = new QsciLexerCSharp();
    coder->setLexer(csharp);

    coder->setMarginType(0, QsciScintilla::NumberMargin);
    coder->setMarginLineNumbers(0, true);
    coder->setMarginWidth(0, 50);
    coder->setAutoCompletionThreshold(1);
    coder->setAutoCompletionSource(QsciScintilla::AcsAll);
    coder->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);

    QFont font = coder->font();
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(10);
    coder->setFont(font);
    coder->setMarginsFont(font);

    QsciAPIs *apis = new QsciAPIs(csharp);
    apis->add(QString("using"));
    apis->add("Console");
    apis->prepare();
}

MainWindow::~MainWindow()
{
    delete ui;
}
