#include "onlinestateselector.h"
#include "ui_onlinestateselector.h"
#include <QMenu>
#include <core.h>
#include "loginwindow.h"

OnlineStateSelector::OnlineStateSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineStateSelector)
{
    enter
    ui->setupUi(this);
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(stateChanged()));
    stateChanged();

    menu = new QMenu(this);
    menu->addAction(QIcon(":/Images/Statuses/online16.png"), tr("Online"), Core::network(), SLOT(goOnline()));
    menu->addAction(QIcon(":/Images/Statuses/2ndline16.png"), tr("2nd line"), Core::network(), SLOT(goDnd()));
    menu->addAction(QIcon(":/Images/Statuses/away16.png"), tr("Away"), Core::network(), SLOT(goAway()));
    menu->addAction(QIcon(":/Images/Statuses/offline16.png"), tr("Offline"), Core::network(), SLOT(goOffline()));
    menu->addSeparator();
    menu->addAction(QIcon(":/Images/MainMenu/relogin.png"), tr("Change account"), this, SLOT(changeAccount()));
    menu->addSeparator();
    menu->addAction(QIcon(":/Images/MainMenu/exit.png"), tr("Exit"), this, SLOT(exit()));
    connect(menu, SIGNAL(aboutToHide()), SLOT(menuClosed()));
    leave
}

OnlineStateSelector::~OnlineStateSelector()
{
    enter
    delete ui;
    leave
}

void OnlineStateSelector::mousePressEvent(QMouseEvent *e)
{
    enter
    ui->widget->setProperty("IsPressed", true);
    ui->widget->setStyleSheet(ui->widget->styleSheet());

    menu->move(this->mapToGlobal(QPoint(0, this->height())));
    menu->show();
    leave
}

void OnlineStateSelector::mouseReleaseEvent(QMouseEvent *e)
{
    enter
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
    leave
}

void OnlineStateSelector::leaveEvent(QEvent *e)
{
    enter
    if (menu->isVisible()) return;
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
    leave
}

void OnlineStateSelector::menuClosed()
{
    enter
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
    leave
}

void OnlineStateSelector::changeAccount()
{
    enter
    Core::network()->goOffline();
    emit Core::ui()->showLoginWindow(false);
    leave
}
void OnlineStateSelector::exit()
{
    enter
    Core::ui()->exit();
    leave
}

void OnlineStateSelector::stateChanged()
{
    enter
    Network::OnlineState state = Core::network()->state();
    switch(state)
    {
        case Network::Online:
            ui->image->setPixmap(QPixmap(":/Images/Statuses/online32.png"));
            ui->text->setText(tr("Online"));
            break;
        case Network::Dnd:
            ui->image->setPixmap(QPixmap(":/Images/Statuses/2ndline32.png"));
            ui->text->setText(tr("2nd line"));
            break;
        case Network::Away:
            ui->image->setPixmap(QPixmap(":/Images/Statuses/away32.png"));
            ui->text->setText(tr("Away"));
            break;
        case Network::Offline:
            if (Core::network()->isConnecting())
            {
                ui->image->setPixmap(QPixmap(":/Images/Statuses/connecting32.png"));
                ui->text->setText(tr("Connecting"));
            }
            else if (!Core::network()->isConnected())
            {
                ui->image->setPixmap(QPixmap(":/Images/Statuses/offline32.png"));
                ui->text->setText(tr("Offline"));
            }
            break;
    }
    leave
}
