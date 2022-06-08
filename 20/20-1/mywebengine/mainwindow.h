#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QWebEngineView;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEngineView *view;

    QLineEdit *locationEdit;
    int progress;


protected slots:
    void changeLocation();
    void setProgress(int);
    void adjustTitle();
    void finishLoading(bool);
};

#endif // MAINWINDOW_H
