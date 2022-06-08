#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

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
    painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(Qt::red, 11));
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    painter.translate(200, 150);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));

    painter.save();
    painter.rotate(90);
    painter.setPen(Qt::cyan);
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    painter.restore();

    painter.setBrush(Qt::darkGreen);
    painter.drawRect(-50, -50, 100, 50);
    painter.save();
    painter.scale(0.5, 0.4);
    painter.setBrush(Qt::yellow);
    painter.drawRect(-50, -50, 100, 50);
    painter.restore();

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkYellow);
    painter.drawEllipse(QRect(60, -100, 50, 50));
    painter.shear(1.5, -0.7);
    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(QRect(60, -100, 50, 50));
}
