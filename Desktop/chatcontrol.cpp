#include "chatcontrol.h"
#include "ui_chatcontrol.h"
#include <QWebView>
#include <QWebFrame>
#include <QDir>
#include "core.h"
#include <QWebInspector>

ChatControl::ChatControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatControl)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui->setupUi(this);    

    connect(ui->web, SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
    connect(ui->web->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(javaScriptWindowObjectCleared()));

    chat = new ChatObject();
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhChat", chat);
    ui->web->setUrl(QUrl::fromLocalFile(qApp->applicationDirPath() + "/VisitorChat.html"));

    connect(Core::network(), SIGNAL(historyLoaded(QString, QVector<BaseNotification*>*)), SLOT(historyLoaded(QString, QVector<BaseNotification*>*)));
    connect(Core::network(), SIGNAL(messageReceived(TextNotification*)), SLOT(messageReceived(TextNotification*)));
    connect(Core::network(), SIGNAL(typingReceived(TypingNotification*)), SLOT(typingReceived(TypingNotification*)));
}

ChatControl::~ChatControl()
{
    delete ui;
}

void ChatControl::setVisitor(Visitor *visitor)
{
    this->_visitor = visitor;
    Core::network()->loadHistory(_visitor->Id);
}

void ChatControl::loadFinished(bool ok)
{
    loadHistoryToChat();
}

void ChatControl::loadHistoryToChat()
{
    if (isHistoryLoaded) return;
    isHistoryLoaded = true;

}

void ChatControl::historyLoaded(QString visitorId, QVector<BaseNotification*>* notifications)
{
    if (_visitor==0) return;
    if (visitorId != _visitor->Id) return;

    for(int i=0;i<notifications->length();i++)
    {
        BaseNotification* notification = notifications->at(i);
        if (notification->inherits("TextNotification"))
        {
            TextNotification* item = dynamic_cast<TextNotification*>(notification);
            QString source = item->IsIncoming ? "Visitor" : "Operator";
            QString displayName = item->IsIncoming ? _visitor->DisplayName() : item->OperatorDisplayName;
            chat->addTextMessage(source, displayName, item->Id, item->Time.toString("hh:mm"), item->Text);
        }
    }
}

void ChatControl::messageReceived(TextNotification* message)
{
    if (message->Text.isEmpty()) return;
    QString source = message->IsIncoming ? "Visitor" : "Operator";
    QString displayName = message->IsIncoming ? _visitor->DisplayName() : message->OperatorDisplayName;
    chat->addTextMessage(source, displayName, message->Id, message->Time.toString("hh:mm"), message->Text);
}

void ChatControl::typingReceived(TypingNotification* message)
{
    if (message->Text.isEmpty()) return;
    chat->addTypingMessage(message->Text);
}

void ChatControl::javaScriptWindowObjectCleared()
{
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhChat", chat);
}

QSize ChatControl::sizeHint() const
{
    QSize size(400,-1);
    return size;
}
