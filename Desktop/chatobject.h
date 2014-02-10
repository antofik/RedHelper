#ifndef CHATOBJECT_H
#define CHATOBJECT_H

#include <QObject>
#include "QXmppMessage.h"

class ChatObject : public QObject
{
    Q_OBJECT
public:
    explicit ChatObject(QObject *parent = 0);    
    //Q_INVOKABLE void addTextMessage(QString source, QString sender, QString message_id, QString time, QString text);
    //Q_INVOKABLE void addInfoMessage(QString time, QString text);

signals:
    void addTextMessage(QString source, QString sender, QString message_id, QString time, QString text);
    void addInfoMessage(QString time, QString text);

public slots:

};

#endif // CHATOBJECT_H
