#ifndef REGEXPPLUGIN_H
#define REGEXPPLUGIN_H
#include <QObject>
#include "regexpinterface.h"  //由plugin.pro中的INCLUDEPATH += D:\QtProject\09\9-4\myplugin\regexpwindow定义

class RegExpPlugin : public QObject, RegExpInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qter.Examples.myplugin.RegExpInterface" FILE "myplugin.json")
    Q_INTERFACES(RegExpInterface)
public:
    QString regexp(const QString &message);
};

#endif // REGEXPPLUGIN_H
