#ifndef NOTIFICATIONPARSER_H
#define NOTIFICATIONPARSER_H

#include <QObject>
#include "QXmppElement.h"
#include "QXmppMessage.h"
#include "QXmppIq.h"
#include "containers.h"

class NotificationParser : public QObject
{
    Q_OBJECT
public:
    explicit NotificationParser(QObject *parent = 0);
    BaseNotification* parse(QXmppElement *element);
    QVector<BaseNotification*>* parse(QXmppIq *iq);
    BaseNotification* MessageToNotification(const QXmppMessage &message);

signals:

public slots:

};

#endif // NOTIFICATIONPARSER_H
