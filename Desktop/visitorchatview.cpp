#include "visitorchatview.h"
#include "ui_visitorchatview.h"
#include "QXmppMessage.h"
#include "core.h"

VisitorChatView::VisitorChatView(Visitor *visitor) : QWidget(0), ui(new Ui::VisitorChatView)
{
    ui->setupUi(this);
    _visitor = visitor;

    connect(ui->cmdSend, SIGNAL(pressed()), SLOT(sendMessage()));
    connect(ui->txtMessage, SIGNAL(sendMessage()), SLOT(sendMessage()));

    ui->chat->setVisitor(_visitor);
    ui->Details->setVisitor(_visitor);

    //undone ui->Cobrowse->setVisitor(_visitor);
}

VisitorChatView::~VisitorChatView()
{
    delete ui;
}

Visitor* VisitorChatView::visitor()
{
    return _visitor;
}
/*
void VisitorChatView::messageReceived(TextMessage *message)
{
    if (message.attribute("content") == "cobrowse")
    {
        ui->Cobrowse->cobrowseReceived(message);
    }
    else if (message.attribute("content") == "mouse")
    {
        ui->Cobrowse->mouseReceived(message);
    }
    else
    {
        ui->chat->messageReceived(message);
    }
    //ui->list->setIndexWidget(item->index(), new QPushButton("test button"));
}
*/
void VisitorChatView::sendMessage()
{
    QString text = ui->txtMessage->toPlainText();
    ui->txtMessage->clear();

    TextNotification *n = new TextNotification();
    prepare(n);
    n->Text = text;
    emit ui->chat->messageReceived(n);

    Core::network()->client->sendMessage(_visitor->Jid, text);
}

void VisitorChatView::prepare(BaseNotification *n)
{
    n->From = Core::network()->MyJid;
    n->To = _visitor->Jid;
    n->IsIncoming = false;
    n->Time = QDateTime::currentDateTime();
    n->Id = QUuid::createUuid().toString();
    n->OperatorDisplayName = Core::network()->MyName;
    n->OperatorLogin = Core::network()->User;
    n->VisitorId = _visitor->Id;
}
