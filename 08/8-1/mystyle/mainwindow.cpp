#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyleFactory>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setStyle(QStyleFactory::create("windows"));
    QPalette palette1 = ui->pushButton->palette();
    palette1.setColor(QPalette::ButtonText, Qt::red);
    palette1.setColor(QPalette::Button, Qt::green);
    ui->pushButton->setPalette(palette1);
    ui->spinBox->setDisabled(true);
    QPalette palette2 = ui->spinBox->palette();
    palette2.setColor(QPalette::Disabled, QPalette::Base, Qt::blue);
    ui->spinBox->setPalette(palette2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
