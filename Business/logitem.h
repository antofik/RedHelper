#ifndef LOGITEM_H
#define LOGITEM_H

#include <QDateTime>

class LogItem
{
public:
    LogItem(int type, QString message);

    int type;
    QString message;
    QDateTime time;

    bool isXmpp;
    bool isIq;
    bool isIncoming;
    bool isMessage;
    bool isOperatorToOperator;
};

#endif // LOGITEM_H
