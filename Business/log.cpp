#include "log.h"
#include "diagnostics.h"

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
    _llog_("Info: " + message)
    emit Log::instance()->added(item);
}

void Log::warning(QString message)
{
    LogItem *item = new LogItem(Log::Warning, QString(message));
    Log::instance()->_items.append(item);
    _llog_("Warning: " + message)
    emit Log::instance()->added(item);
}

void Log::error(QString message)
{
    LogItem *item = new LogItem(Log::Error, QString(message));
    Log::instance()->_items.append(item);
    _llog_("Error: " + message)
    emit Log::instance()->added(item);
}

void Log::xmpp(QString stanza, bool isIncoming, bool isIq, bool isMessage, bool isOperatorToOperator)
{
    LogItem *item = new LogItem(Log::Xmpp, stanza);
    item->isIncoming = isIncoming;
    item->isIq = isIq;
    item->isMessage = isMessage;
    item->isOperatorToOperator = isOperatorToOperator;
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
