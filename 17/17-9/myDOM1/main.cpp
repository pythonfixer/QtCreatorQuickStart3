#include <QCoreApplication>
#include <QtXml>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDomDocument doc;
    QFile file("../myDOM1/my.xml");
    if (!file.open(QIODevice::ReadOnly)) return 0;

    if (!doc.setContent(&file))
    {
        file.close();
        return 0;
    }

    file.close();

    QDomNode firstNode = doc.firstChild();

    qDebug() << qPrintable(firstNode.nodeName()) << qPrintable(firstNode.nodeValue());

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    while (!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();

            qDebug() << qPrintable(e.tagName()) << qPrintable(e.attribute("id"));

            QDomNodeList list = e.childNodes();

            for (int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if (node.isElement())
                    qDebug() << "   " << qPrintable(node.toElement().tagName()) << qPrintable(node.toElement().text());
            }
        }

        n = n.nextSibling();
    }

    return a.exec();
}
