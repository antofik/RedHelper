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
    QWidget *button = ui->tab->tabBar()->tabButton(0, QTabBar::RightSide);
    if (!button) button = ui->tab->tabBar()->tabButton(0, QTabBar::LeftSide);
    if (button) button->hide();

    connect(Core::ui(), SIGNAL(openChat(QString,bool)), SLOT(openChat(QString,bool)));
    connect(ui->tab, SIGNAL(tabCloseRequested(int)), SLOT(tabCloseRequested(int)));
    connect(Core::network(), SIGNAL(messageReceived(QXmppMessage)), SLOT(messageReceived(QXmppMessage)));
}

MainTab::~MainTab()
{
    delete ui;
}

VisitorChatView* MainTab::openChat(QString id, bool activate)
{
    if (!chats->contains(id))
    {
        Visitor *visitor = Core::visitors()->visitorById(id);
        VisitorChatView *chat = new VisitorChatView(visitor);
        int index = ui->tab->addTab(chat, visitor->DisplayName());
        chats->insert(id, chat);
        if (activate) ui->tab->setCurrentIndex(index);
        return chat;
    }
    else
    {
        VisitorChatView *chat = chats->operator [](id);
        if (activate)
            ui->tab->setCurrentWidget(chat);
        return chat;
    }    
}

void MainTab::tabCloseRequested(int index)
{
    QWidget* tab = ui->tab->widget(index);
    VisitorChatView *chat = reinterpret_cast<VisitorChatView*>(tab);
    chats->remove(chat->visitor()->Id);
    ui->tab->removeTab(index);
    delete tab;
}

void MainTab::messageReceived(QXmppMessage message)
{
    QString from = message.from();
    QString to = message.to();
    if (to.indexOf("@") != to.lastIndexOf("@") && !message.attribute("jid").isEmpty())
    {
        from = message.attribute("jid");
    }
    if (from.contains("@visitor"))
    {
        QString vid = from.left(from.indexOf("@"));
        VisitorChatView* chat = openChat(vid, false);
        chat->messageReceived(message);
    }
}
