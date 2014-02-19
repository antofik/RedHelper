#include "logincontrol.h"
#include "ui_logincontrol.h"
#include "core.h"

LoginControl::LoginControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginControl)
{
    ui->setupUi(this);

    connect(ui->cmdLogin, SIGNAL(pressed()), SLOT(login()));
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(networkStateChanged()));
    connect(Core::network(), SIGNAL(XmppError(QXmppStanza::Error::Condition)), SLOT(xmppError(QXmppStanza::Error::Condition)));
    connect(Core::network(), SIGNAL(SocketError(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));

    ui->txtUser->setText(Core::network()->User);
    ui->txtPassword->setText(Core::network()->Password);    
    ui->txtStatus->setText("");

    if (true) //TODO autologin
    {
//        this->login();
    }
}

LoginControl::~LoginControl()
{
    disconnect(Core::network(), SIGNAL(stateChanged()), this, SLOT(networkStateChanged()));
    delete ui;
}

void LoginControl::login()
{
    this->setEnabled(false);
    emit Core::ui()->update();
    ui->txtError->setText("");
    Core::network()->User = ui->txtUser->text();
    Core::network()->Password = ui->txtPassword->text();
    Core::network()->Login();
}

void LoginControl::networkStateChanged()
{
    if (Core::network()->isConnected())
    {
        ui->txtStatus->setText(tr("Logged in."));
        emit Core::ui()->showMainWindow();
        emit hideWindow();
    }
    else if (Core::network()->isConnecting())
    {
        ui->txtStatus->setText(tr("Connecting..."));
        this->setEnabled(false);
    }
}

void LoginControl::xmppError(QXmppStanza::Error::Condition error)
{
    if (error == QXmppStanza::Error::NotAuthorized){
        ui->txtError->setText(tr("Invalid login or password"));
    } else if (error == QXmppStanza::Error::Conflict){
        ui->txtError->setText(tr("Conflict"));
    } else if (error == QXmppStanza::Error::RemoteServerNotFound){
        ui->txtError->setText(tr("Remote server not found"));
    } else if (error == QXmppStanza::Error::RemoteServerTimeout){
        ui->txtError->setText(tr("Remote server timeout"));
    } else if (error == QXmppStanza::Error::ServiceUnavailable){
        ui->txtError->setText(tr("Service unavailable"));
    } else if (error == QXmppStanza::Error::JidMalformed){
        ui->txtError->setText(tr("Invalid charachters in jid"));
    } else {
        ui->txtError->setText(tr("Unknown error: ") + QString::number(error));
    }
    this->setEnabled(true);
}

void LoginControl::socketError(QAbstractSocket::SocketError error)
{
    if (error == QAbstractSocket::RemoteHostClosedError)
    {
        ui->txtError->setText(tr("The remote host closed the connection"));
    }
    else if (error == QAbstractSocket::HostNotFoundError)
    {
        ui->txtError->setText(tr("Host not found"));
    }
    else
    {
        ui->txtError->setText(tr("Network error: ") + QString::number(error));
    }
    this->setEnabled(true);
}
