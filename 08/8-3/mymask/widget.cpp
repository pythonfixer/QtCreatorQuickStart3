#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*QPixmap pixmap(":/image/yafeilinux.png");
    ui->label->setPixmap(pixmap);
    ui->label->setMask(pixmap.mask());*/
    QPixmap pix;
    pix.load(":/image/yafeilinux.png");
    resize(pix.size());
    setMask(pix.mask());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/image/yafeilinux.png"));
}

void Widget::mousePressEvent(QMouseEvent *)
{
    close();
}
