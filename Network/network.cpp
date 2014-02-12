#include "network.h"
#include <Qt>
#include <QtCore>
#include "QXmppMessage.h"
#include "QXmppElement.h"

Network::Network(QObject *parent) :
    QObject(parent)
{
    //default login parameters
    this->Host = "xmpp.redhelper.ru";
    this->port = 443;
    this->User = "antofik";
    this->Password = "@test";
    this->MyJid = this->User + "@xmpp.redhelper.ru";

    //XMPP client
    client = new QXmppClient();
    client->logger()->setLoggingType(QXmppLogger::SignalLogging);
    connect(client, SIGNAL(stateChanged(QXmppClient::State)), SLOT(xmppStateChanged(QXmppClient::State)));
    connect(client, SIGNAL(error(QXmppClient::Error)), SLOT(xmppError(QXmppClient::Error)));
    connect(client, SIGNAL(iqReceived(QXmppIq)), SLOT(xmppIqReceived(QXmppIq)));
    connect(client, SIGNAL(logMessage(QXmppLogger::MessageType,QString)), SLOT(xmppLogMessage(QXmppLogger::MessageType,QString)));
    connect(client, SIGNAL(messageReceived(QXmppMessage)), SLOT(xmppMessageReceived(QXmppMessage)));
    connect(client, SIGNAL(presenceReceived(QXmppPresence)), SLOT(xmppPresenceReceived(QXmppPresence)));
}

void Network::Login()
{
    QXmppConfiguration config;
    config.setDomain("xmpp.redhelper.ru");
    config.setPort(this->port);
    config.setHost(this->Host);
    config.setUser(this->User);
    config.setPassword(this->Password);
    config.setResource("RedHelper");
    client->connectToServer(config);
}

bool Network::isConnected()
{
    return client->isAuthenticated();
}

bool Network::isConnecting()
{
    return client->isConnected() && !client->isAuthenticated();
}

void Network::xmppStateChanged(QXmppClient::State state)
{
    emit StateChanged();

    if (client->isConnected() && client->isAuthenticated())
        sendIqInit();
}

void Network::xmppError(QXmppClient::Error error)
{
    switch(error)
    {
    case QXmppClient::SocketError:
        emit SocketError(client->socketError());
        break;
    case QXmppClient::KeepAliveError:
        break;
    case QXmppClient::XmppStreamError:
        emit XmppError(client->xmppStreamError());
        break;
    }
}

void Network::xmppIqReceived(QXmppIq iq)
{
    if (iq.type()==QXmppIq::Error)
    {

    }
    else if (iq.type()==QXmppIq::Result)
    {
        emit iqReceived(iq);

        if (iq.extensions().count()>0)
        {
            QXmppElement element = iq.extensions().at(0);
            QString ns = element.attribute("xmlns");
            if (ns == "consultant:visitorlistdiff")
            {
                QXmppElement *e = new QXmppElement(element);
                emit visitorListReceived(e);                
            }
            else if (ns == "consultant:init")
            {
                QXmppElement *e = new QXmppElement(element);               
                //todo
                this->MyName = "todo";
            }
            else if (ns == "consultant:history")
            {
                QXmppIq *e = new QXmppIq(iq);
                emit historyLoaded(iq.id(), parser.parse(e));
            }
        }
    }
    else
    {
        qDebug() << "Received unsupported iq";
    }
}

void Network::sendIqInit()
{
    QXmppIq iq;
    QXmppElement query;
    query.setTagName("query");
    query.setAttribute("xmlns", "consultant:init");
    QXmppElement version;
    version.setTagName("version");
    version.setValue(QString::number(1.0));
    query.appendChild(version);
    iq.setExtensions(QXmppElementList() << query);
    client->sendPacket(iq);
}

void Network::xmppLogMessage(QXmppLogger::MessageType type, QString message)
{
   // return;
    if (message.startsWith("<message"))
    if (!message.contains("visitorlistdiff"))
        qDebug() << message;
}

void Network::xmppMessageReceived(const QXmppMessage &message)
{
    auto notification = this->parser.MessageToNotification(message);
    if (auto item = dynamic_cast<TextNotification*>(notification))
    {
        emit messageReceived(item);
    }
    else if (auto item = dynamic_cast<TypingNotification*>(notification))
    {
        emit typingReceived(item);
    }
    else if (auto item = dynamic_cast<MouseNotification*>(notification))
    {
        emit mouseReceived(item);
    }
    else if (auto item = dynamic_cast<CobrowseNotification*>(notification))
    {
        emit cobrowseReceived(item);
    }
    else
    {
        //todo
        qDebug() << "unknown message";
    }
}


void Network::xmppPresenceReceived(QXmppPresence presence)
{
    emit PresenceReceived(presence);
}

void Network::loadHistory(QString visitorId){
    QXmppIq iq;
    QXmppElement query;
    query.setTagName("query");
    query.setAttribute("xmlns", "consultant:history");
    query.setAttribute("jid", visitorId);    
    iq.setExtensions(QXmppElementList() << query);
    iq.setId(visitorId);
    client->sendPacket(iq);
}
