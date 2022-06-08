#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDomDocument doc;

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");

    doc.appendChild(instruction);

    QDomElement root = doc.createElement("书库");
    doc.appendChild(root);

    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;
    id.setValue(QString("1"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Qt");
    title.appendChild(text);
    text = doc.createTextNode("shiming");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    book = doc.createElement("图书");
    id = doc.createAttribute("编号");
    title = doc.createElement("书名");
    author = doc.createElement("作者");
    id.setValue(QString("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Linux");
    title.appendChild(text);
    text = doc.createTextNode("yafei");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QFile file("my.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    QTextStream out(&file);

    doc.save(out, 4);
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doXml(const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("没有找到相关内容！"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("图书");
    for (int i=0; i<list.count(); i++)
    {
        QDomElement e = list.at(i).toElement();
        if (e.attribute("编号") == ui->lineEdit->text())
        {
            if (operate == "delete")
            {
                QDomElement root = doc.documentElement();

                root.removeChild(list.at(i));
                QFile file("my.xml");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return;
                QTextStream out(&file);
                doc.save(out, 4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("删除成功！"));
            }
            else if (operate == "update")
            {
                QDomNodeList child = list.at(i).childNodes();

                child.at(0).toElement().firstChild().setNodeValue(ui->lineEdit_2->text());
                child.at(1).toElement().firstChild().setNodeValue(ui->lineEdit_3->text());
                QFile file("my.xml");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return;
                QTextStream out(&file);
                doc.save(out, 4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("更新成功！"));
            }
            else if (operate == "find")
            {
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName() + e.attribute("编号"));
                QDomNodeList list = e.childNodes();
                for (int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if (node.isElement())
                        ui->listWidget->addItem("   " + node.toElement().tagName() + " : " + node.toElement().text());
                }
            }
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while (!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            ui->listWidget->addItem(e.tagName() + e.attribute("编号"));
            QDomNodeList list = e.childNodes();
            for (int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if (node.isElement())
                    ui->listWidget->addItem("   " + node.toElement().tagName() + " : " + node.toElement().text());
            }
        }
        n = n.nextSibling();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无法添加！"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;

    QString num = root.lastChild().toElement().attribute("编号");
    int count = num.toInt() + 1;
    id.setValue(QString::number(count));
    book.setAttributeNode(id);
    text = doc.createTextNode(ui->lineEdit_2->text());
    title.appendChild(text);
    text = doc.createTextNode(ui->lineEdit_3->text());
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();

    ui->listWidget->clear();
    ui->listWidget->addItem(tr("添加成功！"));
}

void MainWindow::on_pushButton_clicked()
{
    doXml("find");
}

void MainWindow::on_pushButton_2_clicked()
{
    doXml("delete");
}

void MainWindow::on_pushButton_3_clicked()
{
    doXml("update");
}
