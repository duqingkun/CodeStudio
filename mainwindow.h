#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define BREAKPOINT_MARGIN   0
#define LINE_MARGIN  3

namespace Ui {
class MainWindow;
}

class QsciScintilla;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void linesChanged();

private:
    void initUI();

    void initSlots();

private:
    Ui::MainWindow *ui;

    QsciScintilla   *mMainEditor;
};

#endif // MAINWINDOW_H
