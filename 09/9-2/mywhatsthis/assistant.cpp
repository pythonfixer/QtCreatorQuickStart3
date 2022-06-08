#include <QByteArray>
#include <QProcess>
#include <QMessageBox>
#include "assistant.h"

Assistant::Assistant()
    :proc(0)
{

}

Assistant::~Assistant()
{
    if (proc && proc->state() == QProcess::Running)
    {
        proc->terminate();
        proc->waitForFinished(3000);
    }
    delete proc;
}

void Assistant::showDocumentation(const QString &page)
{
    if (!startAssistant())
        return;
    QByteArray ba("SetSource");
    ba.append("qthelp://yafeilinux.myHelp/doc/");
    proc->write(ba + page.toLocal8Bit() + '\n');
}

bool Assistant::startAssistant()
{
    if (!proc)
        proc = new QProcess();
    if (proc->state() != QProcess::Running)
    {
        //QString app = QLatin1String("D:\\QtProject\\09\\9-2\\mywhatsthis\\documentation\\assistant.exe");
        //Win7下默认当前文件夹C:\Users,把mywhatsthis/documentation拷贝到该目录下
        QString app = QLatin1String("../mywhatsthis/documentation/assistant.exe");
        QStringList args;
        args << QLatin1String("-collectionFile") << QLatin1String("../mywhatsthis/documentation/myHelp.qhc");
        proc->start(app, args);
        if (!proc->waitForStarted())
        {
            QMessageBox::critical(0, QObject::tr("my help"), QObject::tr("Unable to launch Qt Assistant (%1)").arg(app));
            return false;
        }
    }
    return true;
}
