#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage image;
    image.load("../mydrawing3/image.png");
    qDebug() << image.size() << image.format() << image.depth();
    painter.drawImage(QPoint(10, 10), image);
    QImage mirror = image.mirrored();
    QTransform transform;
    transform.shear(0.2, 0);
    QImage image2 = mirror.transformed(transform);
    painter.drawImage(QPoint(10, 160), image2);
    image2.save("../mydrawing3/mirror.png");
}
