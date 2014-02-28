#include "visitorchatview.h"
#include "ui_visitorchatview.h"
#include "QXmppMessage.h"
#include "core.h"

VisitorChatView::VisitorChatView(Visitor *visitor) : QWidget(0), ui(new Ui::VisitorChatView)
{
    enter
    ui->setupUi(this);
    _visitor = visitor;

    connect(ui->cmdSend, SIGNAL(pressed()), SLOT(sendMessage()));
    connect(ui->txtMessage, SIGNAL(sendMessage()), SLOT(sendMessage()));
    connect(ui->tabDetails, SIGNAL(currentChanged(int)), SLOT(currentTagChanged(int)));

    ui->chat->setVisitor(_visitor);
    ui->Details->setVisitor(_visitor);
    leave
}

VisitorChatView::~VisitorChatView()
{
    enter
    ui->Cobrowse->stop();
    delete ui;
    leave
}

void VisitorChatView::currentTagChanged(int tabId)
{
    ui->Cobrowse->setVisitor(_visitor);
}

Visitor* VisitorChatView::visitor()
{
    return _visitor;
}

void VisitorChatView::sendMessage()
{
    enter
    QString text = ui->txtMessage->toPlainText();
    ui->txtMessage->clear();

    TextNotification *n = new TextNotification();
    prepare(n);
    n->Text = text;
    emit ui->chat->messageReceived(n);

    Core::network()->client->sendMessage(_visitor->Jid, text);
    leave
}

void VisitorChatView::prepare(BaseNotification *n)
{
    enter
    n->From = Core::network()->MyJid;
    n->To = _visitor->Jid;
    n->IsIncoming = false;
    n->Time = QDateTime::currentDateTime();
    n->Id = QUuid::createUuid().toString();
    n->OperatorDisplayName = Core::network()->MyName;
    n->OperatorLogin = Core::network()->User;
    n->VisitorId = _visitor->Id;
    leave
}
