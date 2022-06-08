#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Assistant;

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
    void startAssistant();

private:
    Ui::MainWindow *ui;
    Assistant *assistant;
};

#endif // MAINWINDOW_H
