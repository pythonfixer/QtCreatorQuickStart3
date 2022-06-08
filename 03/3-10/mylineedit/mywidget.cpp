#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QCompleter>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QValidator *validator = new QIntValidator(100, 999, this);
    ui->lineEdit3->setValidator(validator);

    QStringList wordList;
    wordList << "Qt" << "Qt Creator" << tr("你好");
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit4->setCompleter(completer);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_lineEdit2_returnPressed()
{
    ui->lineEdit3->setFocus();
    qDebug() << ui->lineEdit2->text();
    qDebug() << ui->lineEdit2->displayText();
}
