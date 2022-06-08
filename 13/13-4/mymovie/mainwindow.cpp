#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setBackgroundRole(QPalette::Dark);
    ui->label->setAutoFillBackground(true);
    movie = new QMovie(this);
    movie->setFileName("../mymovie/movie.gif");
    movie->setCacheMode(QMovie::CacheAll);
    QSize size = ui->label->size();
    movie->setScaledSize(size);
    ui->label->setMovie(movie);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(movie->frameCount());
    connect(movie, &QMovie::frameChanged, ui->horizontalSlider, &QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    movie->jumpToFrame(value);
}

void MainWindow::on_pushButton_clicked()
{
    movie->start();
}

void MainWindow::on_pushButton_2_toggled(bool checked)
{
    movie->setPaused(checked);
}

void MainWindow::on_pushButton_3_clicked()
{
    movie->stop();
}

void MainWindow::on_pushButton_4_clicked()
{
    int id = movie->currentFrameNumber();
    QPixmap pix = movie->currentPixmap();
    pix.save(QString("../mymovie/%1.png").arg(id));
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    movie->setSpeed(arg1);
}
