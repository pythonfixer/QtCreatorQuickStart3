#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) return 1;

    QSqlDatabase db1 = QSqlDatabase::database("connection1");
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from student");
    while (query1.next())
    {
        qDebug() << query1.value(0).toInt() << query1.value(1).toString();
    }

    QSqlDatabase db2 = QSqlDatabase::database("connection2");
    QSqlQuery query2(db2);
    qDebug() << "connection2:";
    query2.exec("select * from student");
    while (query2.next())
    {
        qDebug() << query2.value(0).toInt() << query2.value(1).toString();
    }

    int numRows;

    if (db2.driver()->hasFeature(QSqlDriver::QuerySize))
    {
        qDebug() << "has feature: query size";
        numRows = query2.size();
    }
    else
    {
        qDebug() << "no feature: query size";
        query2.last();
        numRows = query2.at() + 1;
    }
    qDebug() << "row number: " << numRows;

    query2.seek(1);

    qDebug() << "current index: " << query2.at();

    QSqlRecord record = query2.record();

    int id = record.value("id").toInt();
    QString name = record.value("name").toString();
    qDebug() << "id: " << id << "name: " << name;

    QSqlField field = record.field(1);
    qDebug() << "second field: " << field.name() << "field value: " << field.value().toString();

    query2.exec("insert into student (id, name) values (100, 'ChenYun')");

    query2.prepare("insert into student (id, name) values (?, ?)");
    QVariantList ids;
    ids << 20 << 21 << 22;
    query2.addBindValue(ids);
    QVariantList names;
    names << "xiaoming" << "xiaoliang" << "xiaogang";
    query2.addBindValue(names);
    if (!query2.execBatch()) qDebug() << query2.lastError();

    query2.exec("update student set name = 'xiaohong' where id = 20");

    query2.exec("delete from student where id = 21");
    return a.exec();
}
