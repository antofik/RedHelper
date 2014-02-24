#include "cobrowseobject.h"
#include <QtCore>
#include <QDebug>
#include "QXmppClient.h"
#include "core.h"
#include "QXmppStanza.h"
#include "QXmppElement.h"
#include "visitor.h"

CobrowseObject::CobrowseObject(Visitor *visitor) : QObject(0)
{
    enter
    _visitor = visitor;
    leave
}

void CobrowseObject::sendMessage(QString type, QString body, QString store)
{
    enter
    QXmppMessage message;
    message.setId(QUuid::createUuid().toString().replace("{","").replace("}",""));
    Visitor* v = _visitor;
    QString s = _visitor->Jid;
    message.setTo(_visitor->Jid);
    message.setBody(body);
    message.setAttribute("content", type.toLower());
    message.setAttribute("store", store);
    Core::network()->client->sendPacket(message);
    leave
}

void CobrowseObject::pushInformation(QString message)
{
    enter
    qDebug() << "pushInformation " << message;
    leave
}

void CobrowseObject::confirmRedirect()
{
    enter
    qDebug() << "confirmRedirect";
    leave
}

void CobrowseObject::stateChanged(QString b1, QString b2, QString b3)
{
    enter
    qDebug() << "stateChanged";
    leave
}
