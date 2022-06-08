#include "widget.h"
#include "ui_widget.h"
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    if (!loadPlugin())
    {
        QMessageBox::information(this, "Error", "Could not load the plugin");
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::loadPlugin()
{
    QDir pluginDir("../plugins");  //Windows默认当前目录为C:\user,需要把生成的plugins拷贝到该目录下
    foreach (QString fileName, pluginDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            regexpInterface = qobject_cast<RegExpInterface *>(plugin);
            if (regexpInterface)
                return true;
        }
    }
    return false;
}

void Widget::on_pushButton_clicked()
{
    QString str = regexpInterface->regexp(ui->lineEdit->text());
    ui->labelNum->setText(str);
}
