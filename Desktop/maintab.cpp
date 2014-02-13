#include "maintab.h"
#include "ui_maintab.h"
#include "QXmppMessage.h"
#include "visitorchatview.h"
#include <QMap>

const QString VISITORS = "Visitors";

MainTab::MainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTab)
{
    ui->setupUi(this);

    chats = new QMap<QString, VisitorChatView*>();
    ui->Stack->setContentsMargins(0, 0, 0, 0);
    ui->Stack->layout()->setContentsMargins(0, 0, 0, 0);
    ui->Stack->layout()->setSpacing(0);

    connect(Core::ui(), SIGNAL(openChat(QString,bool)), SLOT(openChat(QString,bool)));
    connect(Core::ui(), SIGNAL(activateTab(QString)), SLOT(activateTab(QString)));
    connect(Core::ui(), SIGNAL(closeTab(QString)), SLOT(closeTab(QString)));
    connect(Core::ui(), SIGNAL(setTabContent(QString,QWidget*)), SLOT(setTabContent(QString,QWidget*)));
    connect(Core::network(), SIGNAL(messageReceived(TextNotification*)), SLOT(messageReceived(TextNotification*)));
    connect(Core::network(), SIGNAL(typingReceived(TypingNotification*)), SLOT(typingReceived(TypingNotification*)));


    visitorListView = new VisitorListView();
    emit Core::ui()->createTab(VISITORS);
    emit Core::ui()->setTabContent(VISITORS, visitorListView);
    emit Core::ui()->setTabName(VISITORS, tr("Visitors"));
    emit Core::ui()->activateTab(VISITORS);
}

MainTab::~MainTab()
{
    delete ui;
}

void MainTab::activateTab(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    ui->Stack->setCurrentWidget(tabs[tabId]);
}

void MainTab::closeTab(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    ui->Stack->removeWidget(tabs[tabId]);
    tabs.remove(tabId);
}

void MainTab::setTabContent(QString tabId, QWidget *widget)
{
    tabs[tabId] = widget;
    if (widget->layout())
        widget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->Stack->addWidget(widget);
}

VisitorChatView* MainTab::openChat(QString id, bool activate)
{
    if (!chats->contains(id))
    {
        auto visitor = Core::visitors()->visitorById(id);
        VisitorChatView *chat = new VisitorChatView(visitor);
        emit Core::ui()->createTab(visitor->Id);
        emit Core::ui()->setTabContent(visitor->Id, chat);
        emit Core::ui()->setTabName(visitor->Id, visitor->DisplayName());
        chats->insert(id, chat);
        if (activate)
        {
            emit Core::ui()->activateTab(visitor->Id);
        }
        return chat;
    }
    else
    {
        VisitorChatView *chat = chats->operator [](id);
        if (activate)
        {
            emit Core::ui()->activateTab(chat->visitor()->Id);
        }
        return chat;
    }    
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
