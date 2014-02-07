#include "cobrowseobject.h"
#include <QtCore>
#include <QDebug>
#include "QXmppClient.h"
#include "core.h"
#include "QXmppStanza.h"
#include "QXmppElement.h"

CobrowseObject::CobrowseObject(Visitor *parent) : QObject(0)
{
    _visitor = parent;
}

void CobrowseObject::sendMessage(QString type, QString body, QString store)
{
    QXmppMessage message;
    message.setId(QUuid::createUuid().toString().replace("{","").replace("}",""));
    message.setTo(_visitor->Jid);
    message.setBody(body);
    message.setAttribute("content", type.toLower());
    message.setAttribute("store", store);
    Core::network()->client->sendPacket(message);
}
/*
<?xml version="1.0" encoding="utf-16"?>
<message to="30890241@visitor.xmpp.redhelper.ru" xml:lang="ru-ru" id="2fe60200-e413-4159-b23d-5cd23478d6c6" type="chat" displayName="" time="02/06/2014 09:58:34" content="command">
  <body mid="2fe60200-e413-4159-b23d-5cd23478d6c6">{"type":"html"}</body>
</message>
*/

void CobrowseObject::pushInformation(QString message)
{
    qDebug() << "pushInformation " << message;
}

void CobrowseObject::confirmRedirect()
{
    qDebug() << "confirmRedirect";
}

void CobrowseObject::stateChanged(QString b1, QString b2, QString b3)
{
    qDebug() << "stateChanged";
}
