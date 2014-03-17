#ifndef NOTIFICATIONPARSER_H
#define NOTIFICATIONPARSER_H

#include <QObject>
#include "QXmppElement.h"
#include "QXmppMessage.h"
#include "QXmppIq.h"
#include "containers.h"
#include "operator.h"

class NotificationParser : public QObject
{
    Q_OBJECT
public:
    explicit NotificationParser(QObject *parent = 0);
    BaseNotification* parseHistory(QXmppElement *element);
    QVector<BaseNotification*>* parseHistory(QXmppIq *iq, int timeDelta);
    QVector<Operator*>* parseOperators(QXmppIq *iq);
    BaseNotification* MessageToNotification(const QXmppMessage &message);

signals:

public slots:

};

#endif // NOTIFICATIONPARSER_H
