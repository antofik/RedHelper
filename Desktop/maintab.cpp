#include "maintab.h"
#include "ui_maintab.h"
#include "QXmppMessage.h"

MainTab::MainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTab)
{
    ui->setupUi(this);

    chats = new QMap<QString, VisitorChatView*>();

    visitorListView = new VisitorListView();
    ui->tab->addTab(visitorListView, tr("Visitors"));

    //hide close button of visitor list view
    auto button = ui->tab->tabBar()->tabButton(0, QTabBar::RightSide);
    if (!button) button = ui->tab->tabBar()->tabButton(0, QTabBar::LeftSide);
    if (button) button->hide();

    connect(Core::ui(), SIGNAL(openChat(QString,bool)), SLOT(openChat(QString,bool)));
    connect(ui->tab, SIGNAL(tabCloseRequested(int)), SLOT(tabCloseRequested(int)));
    connect(Core::network(), SIGNAL(messageReceived(TextNotification*)), SLOT(messageReceived(TextNotification*)));
    connect(Core::network(), SIGNAL(typingReceived(TypingNotification*)), SLOT(typingReceived(TypingNotification*)));
}

MainTab::~MainTab()
{
    delete ui;
}

VisitorChatView* MainTab::openChat(QString id, bool activate)
{
    if (!chats->contains(id))
    {
        auto visitor = Core::visitors()->visitorById(id);
        auto chat = new VisitorChatView(visitor);
        int index = ui->tab->addTab(chat, visitor->DisplayName());
        chats->insert(id, chat);
        if (activate) ui->tab->setCurrentIndex(index);
        return chat;
    }
    else
    {
        auto chat = chats->operator [](id);
        if (activate)
            ui->tab->setCurrentWidget(chat);
        return chat;
    }    
}

void MainTab::tabCloseRequested(int index)
{
    auto tab = ui->tab->widget(index);
    auto chat = reinterpret_cast<VisitorChatView*>(tab);
    chats->remove(chat->visitor()->Id);
    ui->tab->removeTab(index);
    delete tab;
}

void MainTab::messageReceived(TextNotification *message)
{
    openChatByNotification(message);
}

void MainTab::typingReceived(TypingNotification *message)
{
    openChatByNotification(message);
}

void MainTab::openChatByNotification(BaseNotification* message)
{
    if (message->IsOperatorToOperator) return;
    openChat(message->VisitorId, false);
}
