#include "log.h"

Log::Log(QObject *parent) :
    QObject(parent)
{
}

Log* Log::instance()
{
    static Log instance;
    return &instance;
}

void Log::info(QString message)
{
    LogItem *item = new LogItem(Log::Info, QString(message));
    Log::instance()->_items.append(item);
    emit Log::instance()->added(item);
}

void Log::warning(QString message)
{
    LogItem *item = new LogItem(Log::Warning, QString(message));
    Log::instance()->_items.append(item);
    emit Log::instance()->added(item);
}

void Log::error(QString message)
{
    LogItem *item = new LogItem(Log::Error, QString(message));
    Log::instance()->_items.append(item);
    emit Log::instance()->added(item);
}

void Log::write(LogItem item)
{

}

QVector<LogItem*>* Log::items()
{
    return &Log::instance()->_items;
}
