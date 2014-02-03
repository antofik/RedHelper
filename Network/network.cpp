#include "network.h"
#include <Qt>
#include <QtCore>


Network::Network(QObject *parent) :
    QObject(parent)
{
    client = new QXmppClient();

    connect(client, SIGNAL(stateChanged(QXmppClient::State)), SLOT(xmppStateChanged(QXmppClient::State)));

}

void Network::Login()
{
    QXmppConfiguration config;
    config.setJid("operator@xmpp.redhelper.ru");
    config.setDomain("xmpp.redhelper.ru");
    config.setPort(this->port);
    config.setHost(this->Host);
    config.setUser(this->User);
    config.setPassword(this->Password);
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
}
