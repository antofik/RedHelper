#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "QXmppClient.h"
#include "containers.h"
#include "notificationparser.h"
#include "visitor.h"
#include "redirectnotification.h"

class Network : public QObject
{
    Q_OBJECT

public:
    enum OnlineState
    {
        Offline = 0,
        Away = 1,
        Dnd = 2,
        Online = 3,
    };

    explicit Network(QObject *parent = 0);
    QXmppClient* client;

    void Login();

    bool isConnected();
    bool isConnecting();
    void sendIqInit();
    void loadHistory(QString visitorId);
    OnlineState state();
    void setState(OnlineState state);
    void updateState();

    QString User;
    QString Password;
    QString Host;
    QString MyJid;
    QString MyName;
    QDateTime ServerTime;
    int TimeShift;
    QString ClientEmail;
    QString UpdateChannel;
    QString FirstMessage;
    QString DefaultWelcome;
    int VisitorListInterval;
    int port;

    void sendMessage(QString jid, QString message);

    NotificationParser parser;

public slots:
    void goOnline();
    void goDnd();
    void goAway();
    void goOffline();
    void reconnect();
    void loadOperators();
    void redirectVisitorTo(Visitor* visitor, QString login, QString message);

signals:
    void XmppError(QXmppStanza::Error::Condition error);
    void SocketError(QAbstractSocket::SocketError error);
    void StartWorkers();

    void iqReceived(QXmppIq iq);

    void stateChanged();

    void messageReceived(TextNotification *message);
    void typingReceived(TypingNotification *message);
    void mouseReceived(MouseNotification *message);
    void cobrowseReceived(CobrowseNotification *message);
    void redirectReceived(RedirectNotification *message);

    void visitorListReceived(QXmppElement *);
    void historyLoaded(QString visitorId, QVector<BaseNotification*>* notifications);
    void operatorsLoaded(QVector<Operator*>* operators);

    void logMessage(QString stanza, bool isIncoming, bool isIq, bool isMessage, bool isOperatorToOperator);

private slots:
    void xmppStateChanged(QXmppClient::State state);
    void xmppError(QXmppClient::Error error);
    void xmppIqReceived(QXmppIq iq);
    void xmppLogMessage(QXmppLogger::MessageType type, QString message);
    void xmppMessageReceived(const QXmppMessage &message);
    void xmppPresenceReceived(QXmppPresence presence);
    void xmppDisconnected();

private:
    OnlineState _state;
    OnlineState _wantedState;

};

#endif // NETWORK_H
