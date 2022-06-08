#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QWebEngineView;
class QLineEdit;

class QNetworkAccessManager;

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

    QNetworkAccessManager *manager;


protected slots:
    void changeLocation();
    void setProgress(int);
    void adjustTitle();
    void finishLoading(bool);

    void handleIconUrlChanged(const QUrl &url);
    void handleIconLoaded();
};

#endif // MAINWINDOW_H
