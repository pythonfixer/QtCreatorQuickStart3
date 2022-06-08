#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*ui->pushButton->setStyleSheet("background:yellow");
    ui->horizontalSlider->setStyleSheet("background:blue");
    setStyleSheet("QPushButton{background:yellow} QSlider{background:blue)");*/

    qssFile = new QFile(":/qss/my.qss", this);
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (qssFile->fileName() == ":/qss/my.qss")
        qssFile->setFileName(":/qss/myl.qss");
    else
        qssFile->setFileName(":/qss/my.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
}
