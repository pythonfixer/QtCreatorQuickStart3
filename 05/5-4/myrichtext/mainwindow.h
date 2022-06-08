#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showTextFrame();
    void showTextBlock();
    void setTextFont(bool checked);

    void insertTable();
    void insertList();
    void insertImage();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
