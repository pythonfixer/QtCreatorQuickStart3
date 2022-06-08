#include <QCoreApplication>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QObject::tr("以下是编辑字符串操作:") << endl;
    QString str = "hello";
    qDebug() << QObject::tr("字符串大小:") << str.size();
    str[0] = QChar('H');
    qDebug() << QObject::tr("第一个字符:") << str[0];
    str.append(" Qt");
    str.replace(1, 4, "i");
    str.insert(2, " my");
    qDebug() << QObject::tr("str为:") << str;
    str = str + "!!!";
    qDebug() << QObject::tr("str为:") << str;
    str = " hi\r\n Qt! \n  ";
    qDebug() << QObject::tr("str为:") << str;
    QString str1 = str.trimmed();
    qDebug() << QObject::tr("str1为:") << str1;
    QString str2 = str.simplified();
    qDebug() << QObject::tr("str2为:") << str2;
    str = "hi,my,,Qt";
    QStringList list = str.split(",", QString::SkipEmptyParts);
    qDebug() << QObject::tr("str拆分后为:") << list;
    str = list.join(" ");
    qDebug() << QObject::tr("list组合后为:") << str;
    qDebug() << QString().isNull();
    qDebug() << QString().isEmpty();
    qDebug() << QString("").isNull();
    qDebug() << QString("").isEmpty();

    qDebug() << endl << QObject::tr("以下是在字符串中进行查询的操作:") << endl;
    str = "yafeilinux";
    qDebug() << QObject::tr("字符串为:") << str;
    qDebug() << QObject::tr("包含右侧5个字符的子字符串:") << str.right(5);
    qDebug() << QObject::tr("包含左侧5个字符的子字符串:") << str.left(5);
    qDebug() << QObject::tr("包含第2个字符以后3个字符的子字符串:") << str.mid(2, 3);
    qDebug() << QObject::tr("'fei'的位置:") << str.indexOf("fei");
    qDebug() << QObject::tr("str的第0个字符:") << str.at(0);
    qDebug() << QObject::tr("str中'i'字符的个数:") << str.count('i');
    qDebug() << QObject::tr("str是否以“ya”开始?") << str.startsWith("ya");
    qDebug() << QObject::tr("str是否以“linux”结尾?") << str.endsWith("linux");
    qDebug() << QObject::tr("str是否包含“lin”字符串?") << str.contains("lin");
    QString temp = "hello";
    if (temp > str) qDebug() << temp;
    else qDebug() << str;

    qDebug() << endl << QObject::tr("以下是字符串的转换操作:") << endl;
    str = "100";
    qDebug() << QObject::tr("字符串转换为整数:") << str.toInt();
    int num = 45;
    qDebug() << QObject::tr("整数转换为字符串:") << QString::number(num);
    str = "FF";
    bool ok;
    int hex = str.toInt(&ok, 16);
    qDebug() << "ok:" << ok << QObject::tr("转换为十六进制:") << hex;
    num = 26;
    qDebug() << QObject::tr("使用十六进制将整数转换为字符串:") << QString::number(num, 16);
    str = "123.456";
    qDebug() << QObject::tr("字符串转换为浮点型:") << str.toFloat();
    str = "abc";
    qDebug() << QObject::tr("转换为大写:") << str.toUpper();
    str = "ABC";
    qDebug() << QObject::tr("转换为小写:") << str.toLower();
    int age = 25;
    QString name = "yafei";
    str = QString("name is %1, age is %2").arg(name).arg(age);
    qDebug() << QObject::tr("更改后的str为:") << str;
    str = "%1 %2";
    qDebug() << str.arg("%1f", "hello");
    qDebug() << str.arg("%1f").arg("hello");
    str = QString("ni%1").arg("hi", 5, '*');
    qDebug() << QObject::tr("设置字段宽度为5,使用'*'填充:") << str;
    qreal value = 123.456;
    str = QString("number:%1").arg(value, 0, 'f', 2);
    qDebug() << QObject::tr("设置小数点位数为两位:") << str;
    qDebug() << QObject::tr("将str转换为const char*:") << qPrintable(str);
    return a.exec();
}
