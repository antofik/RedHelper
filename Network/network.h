#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "QXmppClient.h"


class Network : public QObject
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = 0);

    void Login();

    bool isConnected();
    bool isConnecting();

    QString User;
    QString Password;
    QString Host;
    int port;

signals:
    void StateChanged();

private slots:
    void xmppStateChanged(QXmppClient::State state);


private:
    QXmppClient* client;

};

#endif // NETWORK_H
