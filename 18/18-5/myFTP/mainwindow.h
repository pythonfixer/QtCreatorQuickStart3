#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QFtp;
#include <QHash>
class QFile;
class QUrlInfo;
class QTreeWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFtp *ftp;
    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFile *file;

private slots:
    void ftpCommandStarted(int);
    void ftpCommandFinished(int, bool);

    void updateDataTransferProgress(qint64, qint64);
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem *, int);
    void on_connectButton_clicked();
    void on_cdToParentButton_clicked();
    void on_downloadButton_clicked();
};

#endif // MAINWINDOW_H
