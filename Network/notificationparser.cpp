#include "notificationparser.h"
#include <QDebug>
#include <QDateTime>
#include "QXmppMessage.h"
#include "redirectnotification.h"

NotificationParser::NotificationParser(QObject *parent) :
    QObject(parent)
{
}

BaseNotification* NotificationParser::parseHistory(QXmppElement *element)
{
    return 0;
}

QVector<BaseNotification*>* NotificationParser::parseHistory(QXmppIq *iq)
{
    QVector<BaseNotification*> *list = new QVector<BaseNotification*>();
    QXmppElement query = iq->extensions().at(0);
    QXmppElement item = query.firstChildElement("message");
    while(!item.isNull())
    {
        QXmppElement body = item.firstChildElement("body");
        if (!body.isNull() && !body.value().isNull() && !body.value().isEmpty())
        {
            QString text = body.value();
            if (text.startsWith(":r ")) {} //redirect
            else if (text.startsWith(":seize")) {} //seize
            else if (text.startsWith(":notify redirect"))
            {
                RedirectNotification *item = new RedirectNotification();
                item->Type = RedirectNotification::Notify;
                text = text.replace(":notify redirect ", "");
                int i = text.indexOf(' ');
                if (i >= 0)
                {
                    item->Login = text.left(i);
                    item->Message = text.right(text.length() - i - 1);
                }
                else item->Login = text;
                list->append((BaseNotification*)item);
            }
            else if (text.startsWith(":fail")) {} //redirect failed
            else if (text.startsWith(":ok")) {} //redirect succeded
            else if (text.startsWith("###supervising###")) {} //supervising*/
            else
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
        }
        item = item.nextSiblingElement("message");
    }

    return list;
}

QVector<Operator *> *NotificationParser::parseOperators(QXmppIq *iq)
{
    QVector<Operator*>* list = new QVector<Operator*>();
    QXmppElement query = iq->extensions().at(0);
    QXmppElement item = query.firstChildElement("operator");
    while(!item.isNull())
    {
        Operator *o = new Operator();
        o->Login = item.firstChildElement("login").value();
        o->Name = item.firstChildElement("displayName").value();
        o->Avatar = item.firstChildElement("avatar").value();
        o->State = item.firstChildElement("status").value();
        o->Description = item.firstChildElement("description").value();
        o->IsOnDesktop = item.firstChildElement("onDesktop").value() != QString("false");
        QStringList ds = item.firstChildElement("departments").value().split(" ");
        foreach(QString departmentId, ds)
        {
            o->Departments.append(departmentId.toInt());
        }

        list->append(o);

        item = item.nextSiblingElement("operator");
    }
    qDebug() << "Loaded" << list->count() << "operators";
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

        QString text = item->Text;
        if (text.startsWith(":r ")) return nullptr; //redirect
        else if (text.startsWith(":seize ")) return nullptr; //seize
        else if (text.startsWith(":notify redirect"))
        {
            RedirectNotification *item = new RedirectNotification();
            item->Type = RedirectNotification::Notify;
            text = text.replace(":notify redirect ", "");
            int i = text.indexOf(' ');
            if (i >= 0)
            {
                item->Login = text.left(i);
                item->Message = text.right(text.length() - i - 1);
            }
            else item->Login = text;
            result = item;
        }
        else if (text.startsWith(":fail redirect"))
        {
            auto item = new RedirectNotification();
            item->Type = RedirectNotification::Fail;
            result = item;
        }
        else if (text.startsWith(":ok redirect"))
        {
            auto item = new RedirectNotification();
            item->Type = RedirectNotification::Ok;
            result = item;
        }
        else if (text.startsWith("###supervising###")) return nullptr; //supervising*/
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
