#include "maintab.h"
#include "ui_maintab.h"
#include "QXmppMessage.h"
#include "visitorchatview.h"
#include <QMap>
#include "log.h"

#ifdef Q_OS_MAC
#include "notificationcenter.h"
#endif

const QString VISITORS = "Visitors";

MainTab::MainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTab)
{
    enter
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
    connect(Core::ui(), SIGNAL(updateOnlineCount()), SLOT(updateOnlineCount()));

    visitorListView = new VisitorListView();
    emit Core::ui()->createTab(VISITORS, false);
    emit Core::ui()->setTabContent(VISITORS, visitorListView);
    emit Core::ui()->setTabName(VISITORS, tr("Visitors"));
    emit Core::ui()->setTabIcon(VISITORS, ":/Images/List.png");
    emit Core::ui()->activateTab(VISITORS);
    leave
}

MainTab::~MainTab()
{
    enter
    delete ui;
    leave
}

void MainTab::updateOnlineCount()
{
    emit Core::ui()->setTabName(VISITORS, QString(tr("Visitors (%1)")).arg(Core::visitors()->onlineCount()));
}

void MainTab::activateTab(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;
    ui->Stack->setCurrentWidget(tabs[tabId]);
    leave
}

void MainTab::closeTab(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;    
    chats->remove(tabId);
    ui->Stack->removeWidget(tabs[tabId]);
    delete tabs[tabId];
    tabs.remove(tabId);
    leave
}

void MainTab::setTabContent(QString tabId, QWidget *widget)
{
    enter
    tabs[tabId] = widget;
    if (widget->layout())
        widget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->Stack->addWidget(widget);
    leave
}

VisitorChatView* MainTab::openChat(QString id, bool activate)
{
    enter
    Log::info("Opening chat for visitor " + id);
    VisitorChatView *chat;
    if (!chats->contains(id))
    {
        Visitor* visitor = Core::visitors()->visitorById(id);
        chat = new VisitorChatView(visitor);
        Log::info("creating new chat");
        emit Core::ui()->createTab(visitor->Id, true);
        emit Core::ui()->setTabContent(visitor->Id, chat);
        emit Core::ui()->setTabName(visitor->Id, visitor->DisplayName());
        emit Core::ui()->setTabIcon(visitor->Id, ":/Images/Customer.png");
        chats->insert(id, chat);
        if (activate)
        {
            emit Core::ui()->activateTab(visitor->Id);
        }
    }
    else
    {
        Log::info("chat found (already exists)");
        chat = chats->operator [](id);
        if (activate)
        {
            emit Core::ui()->activateTab(chat->visitor()->Id);
        }        
    }    
    emit Core::ui()->highlight(chat->visitor()->Id);

    leave
    return chat;
}

void MainTab::messageReceived(TextNotification *message)
{
    enter
    Log::info("MainTab::messageReceived(" + message->Text + ")");
    openChatByNotification(message);
    if (!Core::ui()->isActive())
    {
#ifdef Q_OS_MAC
        NotificationCenter::instance()->test();
#endif
        Core::ui()->playSound();
    }
    leave
}

void MainTab::typingReceived(TypingNotification *message)
{
    enter
    Log::info("MainTab::typingReceived(" + message->Text + ")");
    openChatByNotification(message);
    if (!Core::ui()->isActive()) Core::ui()->playSound();
    leave
}

void MainTab::openChatByNotification(BaseNotification* message)
{
    enter
    if (message->IsOperatorToOperator)
    {
        Log::info("message is from operator to operator. Skipping");
    }
    else
    {
        openChat(message->VisitorId, false);
    }
    leave
}
