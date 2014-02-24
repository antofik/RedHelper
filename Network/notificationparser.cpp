#include "notificationparser.h"
#include <QDebug>
#include <QDateTime>
#include "QXmppMessage.h"

NotificationParser::NotificationParser(QObject *parent) :
    QObject(parent)
{
}

BaseNotification* NotificationParser::parse(QXmppElement *element)
{

}

QVector<BaseNotification*>* NotificationParser::parse(QXmppIq *iq)
{
    QVector<BaseNotification*> *list = new QVector<BaseNotification*>();
    QXmppElement query = iq->extensions().at(0);
    QXmppElement item = query.firstChildElement("message");
    while(!item.isNull())
    {
        QXmppElement body = item.firstChildElement("body");
        if (!body.isNull() && !body.value().isNull() && !body.value().isEmpty())
        {
            TextNotification *n = new TextNotification();
            n->Id = body.attribute("mid");
            n->Text = body.value();
            n->From = item.attribute("from");
            n->To = item.attribute("to");
            n->IsIncoming = n->From.contains("@visitor.");
            n->OperatorDisplayName = item.attribute("displayName");
            n->Time = QDateTime::fromString(item.attribute("time"), "yyyy-MM-dd HH:mm:ss");
            list->append(n);
        }
        item = item.nextSiblingElement("message");
    }

    return list;
}

BaseNotification* NotificationParser::MessageToNotification(const QXmppMessage &message)
{
    auto content = message.attribute("content");
    if (content.isEmpty()) content = "normal";
    auto type = message.attribute("type");

    BaseNotification *result;
    if (content == "normal")
    {
        auto item = new TextNotification();
        item->Text = message.body();
        item->OperatorDisplayName = message.attribute("displayName");
        result = item;
    }
    else if (content == "partial")
    {
        auto item = new TypingNotification();
        item->Text = message.body();
        result = item;
    }
    else if (content == "cobrowse")
    {
        auto item = new CobrowseNotification();
        item->Data = message.body();
        result = item;
    }
    else if (content == "mouse")
    {
        auto item = new MouseNotification();
        item->Data = message.body();
        result = item;
    }
    else
    {
        return nullptr;
    }

    result->Id = message.id();
    result->From = message.from();
    result->To = message.to();
    auto m = message.attribute("time");
    result->Time = QDateTime::fromString(message.attribute("time"), "yyyy-MM-dd hh:mm:ss");

    if (result->From.contains("@visitor"))
    {
        result->IsIncoming = true;
        result->VisitorId = result->From.left(result->From.indexOf("@"));
        result->OperatorLogin = result->To.left(result->To.indexOf("@"));
    }
    else if (result->To.contains("@visitor"))
    {
        result->IsIncoming = false;
        result->VisitorId = result->To.left(result->To.indexOf("@"));
        result->OperatorLogin = result->From.left(result->From.indexOf("@"));
    }
    else
    {
        result->IsOperatorToOperator = true;
        result->FromOperator = result->From.left(result->From.indexOf("@"));
        result->ToOperator = result->To.left(result->To.indexOf("@"));
    }

    return result;
}
