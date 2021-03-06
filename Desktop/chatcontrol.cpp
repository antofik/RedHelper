#include "chatcontrol.h"
#include "ui_chatcontrol.h"
#include <QWebView>
#include <QWebFrame>
#include <QDir>
#include "core.h"
#include <QWebInspector>
#include "log.h"
#include <QSound>

ChatControl::ChatControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatControl)
{
    chat = 0;
    _visitor = 0;
    isHistoryLoaded = false;

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
    connect(Core::network(), SIGNAL(redirectReceived(RedirectNotification*)), SLOT(redirectReceived(RedirectNotification*)));
}

ChatControl::~ChatControl()
{
    qDebug() << "~ChatControl()";
    delete ui;
    ui = 0;
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
    emit chat->markLoaded();

    for(int i=0;i<notifications->length();i++)
    {
        BaseNotification* notification = notifications->at(i);
        if (auto item = dynamic_cast<TextNotification*>(notification))
        {
            QString source = item->IsIncoming ? "Visitor" : "Operator";
            QString displayName = item->IsIncoming ? _visitor->DisplayName() : item->OperatorDisplayName;
            emit chat->addTextMessage(source, displayName, item->Id, item->Time.toString("hh:mm"), item->Text);
            if (i%10==0) emit Core::ui()->update();
            if (ui==0) return; //chat was destroyed
        }        
        else if (auto item = dynamic_cast<RedirectNotification*>(notification))
        {
            emit chat->redirected(tr("Visitor was redirected to you with message: %1").arg(item->Message));
            if (i%10==0) emit Core::ui()->update();
            if (ui==0) return; //chat was destroyed
        }
    }
}

void ChatControl::messageReceived(TextNotification* message)
{
    if (message->VisitorId != _visitor->Id) return;
    Log::info("ChatControl::messageReceived("+message->Text+")");
    if (message->Text.isEmpty()) return;
    QString source = message->IsIncoming ? "Visitor" : "Operator";
    QString displayName = message->IsIncoming ? _visitor->DisplayName() : message->OperatorDisplayName;
    emit chat->addTextMessage(source, displayName, message->Id, message->Time.toString("hh:mm"), message->Text);
}

void ChatControl::startRedirect(QString name, QString message)
{
    emit chat->startRedirect(message);
}

void ChatControl::seize(QString message)
{
    _visitor->CurrentOperator = Core::network()->User;
    emit chat->seize(message);
}

void ChatControl::typingReceived(TypingNotification* message)
{
    if (message->VisitorId != _visitor->Id) return;
    if (message->Text.isEmpty()) return;
    chat->addTypingMessage(message->Text);
}

void ChatControl::redirectReceived(RedirectNotification *message)
{
    if (message->VisitorId != _visitor->Id) return;
    if (message->Type == RedirectNotification::Notify)
    {
        _visitor->CurrentOperator = Core::network()->User;
        emit chat->redirected(tr("Visitor was redirected to you with message: %1").arg(message->Message));
    }
    else if (message->Type == RedirectNotification::Ok && _visitor->isRedirecting)
    {
        emit chat->confirmRedirect(tr("Redirection was successful"));
    }
    else if (message->Type == RedirectNotification::Fail && _visitor->isRedirecting)
    {
        emit chat->failRedirect(tr("Redirection failed"));
    }
    _visitor->isRedirecting = false;

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













