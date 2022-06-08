#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "Available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach (QString driver, drivers)
        qDebug() << driver;
    return app.exec();
}
