#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qsciapis.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , mMainEditor(0)
{
    ui->setupUi(this);

    initUI();

    initSlots();

    QsciLexerCSharp *csharp = new QsciLexerCSharp();
    mMainEditor->setLexer(csharp);

    QFont font = mMainEditor->font();
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(10);
    mMainEditor->setFont(font);
    mMainEditor->setMarginsFont(font);

    QsciAPIs *apis = new QsciAPIs(csharp);
    apis->add(QString("using"));
    apis->add("Console");
    apis->prepare();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linesChanged()
{
    int bits = QString::number(mMainEditor->lines()).length();
    mMainEditor->setMarginWidth(LINE_MARGIN, QString(bits, QChar('0')));
}

void MainWindow::initUI()
{
    mMainEditor = new QsciScintilla;
    this->setCentralWidget(mMainEditor);

    //行号
    mMainEditor->setMarginsForegroundColor(Qt::black);       //字体颜色
    mMainEditor->setMarginType(LINE_MARGIN, QsciScintilla::NumberMargin);
    mMainEditor->setMarginLineNumbers(LINE_MARGIN, true);
    mMainEditor->setMarginWidth(LINE_MARGIN, "0");

    //行号区的图标
    mMainEditor->setMarginType(BREAKPOINT_MARGIN, QsciScintilla::SymbolMargin);
    mMainEditor->setMarginWidth(BREAKPOINT_MARGIN, "00000");
    //mMainEditor->markerDefine();  //设置相应margin鼠标点击后显示的图标,如断点等
    mMainEditor->markerDefine(QsciScintilla::Circle, 0);
    mMainEditor->markerAdd(0, 0);   //测试 0表示第一行

    //自动补全
    mMainEditor->setAutoCompletionThreshold(1);
    mMainEditor->setAutoCompletionSource(QsciScintilla::AcsAll);

    //编码
    mMainEditor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);

    //自动换行
    mMainEditor->setWrapMode(QsciScintilla::WrapWord);
    mMainEditor->setWrapVisualFlags(QsciScintilla::WrapFlagByText);
    mMainEditor->setWrapIndentMode(QsciScintilla::WrapIndentIndented);

    //缩进
    mMainEditor->setIndentationsUseTabs(false); //false:空格 true:tab
    mMainEditor->setTabWidth(4);
    //mMainEditor->setIndentationGuides(true);    //是否显示tab位置对齐线
    mMainEditor->setAutoIndent(true);           //换行自动缩进

    //
}

void MainWindow::initSlots()
{
    connect(mMainEditor, &QsciScintilla::linesChanged, this, &MainWindow::linesChanged);
}
