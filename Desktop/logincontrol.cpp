#include "logincontrol.h"
#include "ui_logincontrol.h"
#include "core.h"

LoginControl::LoginControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginControl)
{
    ui->setupUi(this);

    connect(ui->cmdLogin, SIGNAL(pressed()), SLOT(login()));
    connect(Core::network(), SIGNAL(StateChanged()), SLOT(networkStateChanged()));

    ui->txtUser->setText(Core::network()->User);
    ui->txtPassword->setText(Core::network()->Password);
}

LoginControl::~LoginControl()
{
    delete ui;
}

void LoginControl::login()
{
    Core::network()->User = ui->txtUser->text();
    Core::network()->Password = ui->txtPassword->text();
    Core::network()->Login();
}

void LoginControl::networkStateChanged()
{
    if (Core::network()->isConnected())
    {
        emit hideWindow();
    }
    else if (Core::network()->isConnecting())
    {
        this->setEnabled(false);
    }
    else
    {
        this->setEnabled(true);
    }
}
