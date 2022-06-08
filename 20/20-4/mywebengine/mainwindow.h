#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class WebView;
class QLineEdit;

class QNetworkAccessManager;

#include <QModelIndex>
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    WebView *createView();

private:
    Ui::MainWindow *ui;
    WebView *view;

    QLineEdit *locationEdit;
    int progress;

    QNetworkAccessManager *manager;

    QListWidget *historyList;

    QLineEdit *findEdit;


protected slots:
    void changeLocation();
    void setProgress(int);
    void adjustTitle();
    void finishLoading(bool);

    void handleIconUrlChanged(const QUrl &url);
    void handleIconLoaded();

    void showHistory();
    void gotoHistory(const QModelIndex &index);
};

#endif // MAINWINDOW_H
