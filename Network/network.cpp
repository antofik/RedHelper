#include "network.h"
#include <Qt>
#include <QtCore>
#include "QXmppMessage.h"
#include "QXmppElement.h"
#include "diagnostics.h"
#include <QSettings>
#include <QDebug>
#include "redirectnotification.h"

Network::Network(QObject *parent) :
    QObject(parent),
    _state(OnlineState::Offline),
    _wantedState(OnlineState::Online)
{
    enter

    QSettings settings;

    //default login parameters
    this->Host = "xmpp.redhelper.ru";
    this->port = 443;
    this->User = settings.value("user", "").toString();
    this->Password = settings.value("password", "").toString();
    this->MyJid = this->User + "@xmpp.redhelper.ru";

    //XMPP client
    client = new QXmppClient();
    client->logger()->setLoggingType(QXmppLogger::SignalLogging);
    connect(client, SIGNAL(disconnected()), SLOT(xmppDisconnected()));
    connect(client, SIGNAL(stateChanged(QXmppClient::State)), SLOT(xmppStateChanged(QXmppClient::State)));
    connect(client, SIGNAL(error(QXmppClient::Error)), SLOT(xmppError(QXmppClient::Error)));
    connect(client, SIGNAL(iqReceived(QXmppIq)), SLOT(xmppIqReceived(QXmppIq)));
    connect(client, SIGNAL(logMessage(QXmppLogger::MessageType,QString)), SLOT(xmppLogMessage(QXmppLogger::MessageType,QString)));
    connect(client, SIGNAL(messageReceived(QXmppMessage)), SLOT(xmppMessageReceived(QXmppMessage)));
    connect(client, SIGNAL(presenceReceived(QXmppPresence)), SLOT(xmppPresenceReceived(QXmppPresence)));     

    leave
}

void Network::Login()
{
    enter
    QXmppConfiguration config;
    config.setDomain("xmpp.redhelper.ru");
    config.setPort(this->port);
    config.setHost(this->Host);
    config.setUser(this->User);
    config.setPassword(this->Password);
    config.setResource("RedHelper");
    config.setAutoReconnectionEnabled(true);

    QSettings settings;
    settings.setValue("user", User);
    settings.setValue("password", Password);
    settings.sync();

    client->connectToServer(config);
    leave
}

bool Network::isConnected()
{
    return client->isAuthenticated() && _state != Network::Offline;
}

bool Network::isConnecting()
{
    return client->isConnected() && !isConnected();
}

void Network::xmppStateChanged(QXmppClient::State state)
{
    enter
    if (client->isConnected() && client->isAuthenticated())
    {
        updateState();
        sendIqInit();
    }
    else if (state == QXmppClient::DisconnectedState)
    {
        _state = OnlineState::Offline;
    }

    emit stateChanged();
    leave
}

void Network::xmppDisconnected()
{
    enter
    leave
}

void Network::xmppError(QXmppClient::Error error)
{
    enter
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
    leave
}

void Network::xmppIqReceived(QXmppIq iq)
{
    enter
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
                QXmppElement *q = new QXmppElement(element);
                MyName = q->firstChildElement("displayName").value();
                ServerTime = QDateTime::fromString(q->firstChildElement("time").value(), "yyyy-MM-dd hh:mm:ss");
                TimeShift = ServerTime.secsTo(QDateTime::currentDateTime());
                qDebug() << "INit: " << ServerTime << QTime::currentTime() << TimeShift;
                ClientEmail = q->firstChildElement("clientEmail").value();
                FirstMessage = q->firstChildElement("firstMessage").value();
                DefaultWelcome = q->firstChildElement("defaultWelcome").value();
                VisitorListInterval = q->firstChildElement("visitorListInterval").value().toInt();
            }
            else if (ns == "consultant:history")
            {
                QXmppIq *e = new QXmppIq(iq);
                emit historyLoaded(iq.id(), parser.parseHistory(e, TimeShift));
            }
            else if (ns == "consultant:operatorlist")
            {
                QXmppIq *e = new QXmppIq(iq);
                emit operatorsLoaded(parser.parseOperators(e));
            }
            else
            {
                qDebug() << "Unknown Iq received:" << ns;
            }
        }
    }
    else
    {
        qDebug() << "Received unsupported iq";
    }
    leave
}

void Network::sendIqInit()
{
    enter
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
    leave
}

void Network::xmppLogMessage(QXmppLogger::MessageType type, QString message)
{
    //if (message.startsWith("<message"))    
    QString direction = type == QXmppLogger::ReceivedMessage ? "<=" : "=>";
    _log_(direction + "\t" + message)
    //return;
    if (!message.contains("visitorlistdiff"))
        qDebug() << direction << " " << message;

    emit logMessage(message, type == QXmppLogger::ReceivedMessage, message.startsWith("<iq"), message.startsWith("<message"), false);
}

void Network::xmppMessageReceived(const QXmppMessage &message)
{
    enter
    BaseNotification *notification = parser.MessageToNotification(message);
    if (notification==nullptr) return;
    notification->Time = notification->Time.addSecs(TimeShift);
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
    else if (auto item = dynamic_cast<RedirectNotification*>(notification))
    {
        emit redirectReceived(item);
        if (item->Type == RedirectNotification::Notify){
            client->sendMessage(item->From, ":ok redirect " + User);
        }
    }
    else
    {
        //todo
        qDebug() << "unknown message";
    }
    leave
}

void Network::xmppPresenceReceived(QXmppPresence presence)
{
    enter
    qDebug() << "Presence received";
    if (presence.type()==QXmppPresence::Unavailable && _state != OnlineState::Offline)
    {
        _state = OnlineState::Offline;
        qDebug() << " - unavailable";
        emit stateChanged();
    }
    else
    {
        OnlineState newState;
        auto state = presence.availableStatusType();
        qDebug() << " -" << state;
        if (state == QXmppPresence::DND)
            newState = OnlineState::Dnd;
        else if (state == QXmppPresence::Away)
            newState = OnlineState::Away;
        else
            newState = OnlineState::Online;        
        if (newState != _state)
        {
            _state = newState;
            emit stateChanged();
        }
    }
    qDebug() << "New state =" << _state;
    leave
}

void Network::loadHistory(QString visitorId)
{
    enter
    QXmppIq iq;
    QXmppElement query;
    query.setTagName("query");
    query.setAttribute("xmlns", "consultant:history");
    query.setAttribute("limit", "7");
    query.setAttribute("jid", visitorId);    
    iq.setExtensions(QXmppElementList() << query);
    iq.setId(visitorId);
    client->sendPacket(iq);
    leave
}

Network::OnlineState Network::state()
{
    return _state;
}

void Network::setState(OnlineState state)
{
    enter
    _wantedState = state;
    if (isConnected())
        updateState();
    else
        reconnect();
    leave
}

void Network::reconnect()
{
    enter
    Login();
    leave
}

void Network::loadOperators()
{
    enter
    qDebug() << "Network::loadOperators()";
    if (client->isConnected() && client->isAuthenticated())
    {
        try
        {
            QXmppIq iq;
            QXmppElement query;
            query.setTagName("query");
            query.setAttribute("xmlns", "consultant:operatorlist");
            iq.setExtensions(QXmppElementList() << query);
            client->sendPacket(iq);
        }
        catch (const std::exception& ex)
        {
            qDebug() << "OperatorList Error" << ex.what();
        }
        catch (const std::string& ex)
        {
            qDebug() << "OperatorList Error" << QString(ex.data());
        }
        catch(...)
        {
            qDebug() << "OperatorList Error";
        }
    }

    leave
}

void Network::redirectVisitorTo(Visitor *visitor, QString login, QString message)
{
    enter
    client->sendMessage(visitor->Jid, ":r " + login + " " + message);
    leave
}

void Network::updateState()
{
    enter            
    qDebug() << "Updating state to wantedState =" << _wantedState;
    QXmppPresence presence(_wantedState == OnlineState::Offline ? QXmppPresence::Unavailable : QXmppPresence::Available);
    if (_wantedState == OnlineState::Online)
        presence.setAvailableStatusType(QXmppPresence::Online);
    else if (_wantedState == OnlineState::Away)
        presence.setAvailableStatusType(QXmppPresence::Away);
    else if (_wantedState == OnlineState::Dnd)
        presence.setAvailableStatusType(QXmppPresence::DND);
    client->sendPacket(presence);
    leave
}

void Network::sendMessage(QString jid, QString message)
{
    QXmppMessage m("", jid, message);
    m.setId(QUuid::createUuid().toString().replace("{","").replace("}",""));
    m.setAttribute("content", "normal");
    m.setAttribute("displayName", MyName);
    m.setAttribute("time", QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss"));
    client->sendPacket(m);
}

void Network::goOnline()
{
    enter
    setState(OnlineState::Online);
    leave
}

void Network::goDnd()
{
    enter
    setState(OnlineState::Dnd);
    leave
}

void Network::goAway()
{
    enter
    setState(OnlineState::Away);
    leave
}

void Network::goOffline()
{
    enter
    client->disconnectFromServer();
    leave
}























