#include "logincontrol.h"
#include "ui_logincontrol.h"
#include "core.h"

LoginControl::LoginControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginControl)
{
    enter
    ui->setupUi(this);

    connect(ui->cmdLogin, SIGNAL(pressed()), SLOT(login()));
    connect(ui->cmdCancel, SIGNAL(pressed()), SLOT(cancel()));
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(networkStateChanged()));
    connect(Core::network(), SIGNAL(XmppError(QXmppStanza::Error::Condition)), SLOT(xmppError(QXmppStanza::Error::Condition)));
    connect(Core::network(), SIGNAL(SocketError(QAbstractSocket::SocketError)), SLOT(socketError(QAbstractSocket::SocketError)));

    ui->txtUser->setText(Core::network()->User);
    ui->txtPassword->setText(Core::network()->Password);    
    ui->txtStatus->setText("");

    QSettings settings;
    ui->chkAutologin->setChecked(settings.value("autologin", false).toBool());

    if (ui->chkAutologin->isChecked())
    {
        emit login();
    }

    leave
}

LoginControl::~LoginControl()
{
    enter
    disconnect(Core::network(), SIGNAL(stateChanged()), this, SLOT(networkStateChanged()));
    delete ui;
    leave
}

void LoginControl::login()
{
    enter
    enableEditing(false);
    emit Core::ui()->update();
    ui->txtError->setText("");
    Core::network()->User = ui->txtUser->text();
    Core::network()->Password = ui->txtPassword->text();
    Core::network()->Login();

    QSettings settings;
    settings.setValue("autologin", ui->chkAutologin->isChecked());
    settings.sync();
    leave
}

void LoginControl::cancel()
{
    enter
    emit Core::ui()->exit();
    leave
}

void LoginControl::enableEditing(bool ok)
{
    enter
    ui->txtUser->setEnabled(ok);
    ui->txtPassword->setEnabled(ok);
    ui->cmdLogin->setEnabled(ok);
    ui->chkAutologin->setEnabled(ok);
    leave
}

void LoginControl::networkStateChanged()
{
    enter
    if (Core::network()->isConnected())
    {
        ui->txtStatus->setText(tr("Logged in."));
        emit Core::ui()->showMainWindow();
        emit hideWindow();
    }
    else if (Core::network()->isConnecting())
    {
        ui->txtStatus->setText(tr("Connecting..."));
        enableEditing(false);
    }
    leave
}

void LoginControl::xmppError(QXmppStanza::Error::Condition error)
{
    enter
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
    enableEditing(true);
    leave
}

void LoginControl::socketError(QAbstractSocket::SocketError error)
{
    enter
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
    enableEditing(true);
    leave
}
