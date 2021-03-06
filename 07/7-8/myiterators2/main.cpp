#include <QCoreApplication>
#include <QMapIterator>
#include <QMutableMapIterator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMap<QString, QString> map;
    map.insert("Paris", "France");
    map.insert("Guatemala City", "Guatemala");
    map.insert("Mexico City", "Mexico");
    map.insert("Moscow", "Russia");
    QMapIterator<QString, QString> i(map);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << " : " << i.value();
    }
    if (i.findPrevious("Mexico"))
        qDebug() << "find 'Mexico'";
    QMutableMapIterator<QString, QString> j(map);
    while (j.hasNext())
    {
        if (j.next().key().endsWith("City"))
            j.remove();
    }
    while (j.hasPrevious())
    {
        j.previous();
        qDebug() << j.key() << " : " << j.value();
    }
    return a.exec();
}
