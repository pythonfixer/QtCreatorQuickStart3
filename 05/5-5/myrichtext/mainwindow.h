#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QDialog;

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

    void textFind();
    void findNext();

private:
    Ui::MainWindow *ui;

    QLineEdit *lineEdit;
    QDialog *findDialog;
};

#endif // MAINWINDOW_H
