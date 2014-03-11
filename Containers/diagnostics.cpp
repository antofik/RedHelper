#include "diagnostics.h"
#include <QFile>
#include <QDateTime>
#include <Qt>
#include <QtCore>
#include <QCoreApplication>

Diagnostics::Diagnostics(QObject *parent) :
    QObject(parent)
{    
    QFile file("./redhelper.log");
    file.open(QFile::Truncate | QFile::ReadWrite | QFile::Text);
    file.write((QString("Starting logging ") + QDateTime::currentDateTime().toString()).toUtf8() + "\n\n");
    file.flush();
    file.close();
}

Diagnostics *Diagnostics::instance()
{
    static Diagnostics instance;
    static QThread thread;
    instance.moveToThread(&thread);
    thread.start();
    return &instance;
}

void Diagnostics::Log(const QString value)
{
    emit Diagnostics::instance()->write(value);
}

void Diagnostics::write(const QString value)
{
    QFile file("./redhelper.log");
    if (file.size()>LOG_FILE_LIMIT)
    {
        rotateLogs();
    }
    file.open(QFile::Append | QFile::Text);
    file.write(QDateTime::currentDateTime().toString("hh:mm:ss.zzz\t").toUtf8());
    file.write(value.toUtf8());
    file.write(QString("\n").toUtf8());
    file.close();
}

void Diagnostics::rotateLogs()
{
    QFile::remove("./redhelper" + QString::number(LOG_FILES_COUNT-1) + ".log");
    QDir dir = QDir::current();
    for(int i=LOG_FILES_COUNT-2;i>0;i--)
    {
        dir.rename("./redhelper" + QString::number(i) + ".log", "./redhelper" + QString::number(i+1) + ".log");
    }
    dir.rename("./redhelper.log", "./redhelper1.log");
}
