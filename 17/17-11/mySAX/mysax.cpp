#include "mysax.h"
#include <QtXml>
#include <QListWidget>

MySAX::MySAX()
{
    list = new QListWidget;
    list->show();
}

MySAX::~MySAX()
{
    delete list;
}

bool MySAX::readFile(const QString &fileName)
{
    QFile file(fileName);

    QXmlInputSource inputSource(&file);

    QXmlSimpleReader reader;

    reader.setContentHandler(this);

    reader.setErrorHandler(this);

    return reader.parse(inputSource);
}

bool MySAX::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "library")
        list->addItem(qName);
    else if (qName == "book")
        list->addItem("    " + qName + atts.value("id"));
    return true;
}

bool MySAX::characters(const QString &ch)
{
    currentText = ch;
    return true;
}

bool MySAX::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName == "title" || qName == "author")
        list->addItem("        " + qName + " : " + currentText);
    return true;
}

bool MySAX::fatalError(const QXmlParseException &exception)
{
    qDebug() << exception.message();
    return false;
}
