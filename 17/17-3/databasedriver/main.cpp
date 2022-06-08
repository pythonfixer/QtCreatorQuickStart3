#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>

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
    return a.exec();
}
