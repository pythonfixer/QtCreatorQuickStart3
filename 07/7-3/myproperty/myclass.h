#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)

public:
    explicit MyClass(QObject *parent = 0);
    QString getUserName() const
    { return m_userName; }
    void setUserName(QString userName)
    {
        m_userName = userName;
        emit userNameChanged(userName);
    }

signals:
    void userNameChanged(QString);

private:
    QString m_userName;

public slots:
};

#endif // MYCLASS_H
