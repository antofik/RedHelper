#ifndef COBROWSEOBJECT_H
#define COBROWSEOBJECT_H

#include <QObject>
#include "visitor.h"
#include "QXmppMessage.h"

class CobrowseObject : public QObject
{
    Q_OBJECT
public:
    CobrowseObject(Visitor *parent);
    Q_INVOKABLE void sendMessage(QString type, QString body, QString store);
    Q_INVOKABLE void pushInformation(QString message);
    Q_INVOKABLE void confirmRedirect();
    Q_INVOKABLE void stateChanged(QString b1, QString b2, QString b3);

signals:
    /*void redirectResult(QString ok);
    void messageReceived(QString base64message);
    void moveMouse(QString data);
    void redirect();
    void follow();
    void highlight();*/

public slots:
    //void sendMessage(QString type, QString body, QString store);

private:
    Visitor* _visitor;
};

#endif // COBROWSEOBJECT_H
