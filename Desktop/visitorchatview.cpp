#include "visitorchatview.h"
#include "ui_visitorchatview.h"
#include "QXmppMessage.h"
#include "core.h"

VisitorChatView::VisitorChatView(Visitor *visitor) : QWidget(0), ui(new Ui::VisitorChatView)
{
    ui->setupUi(this);
    _visitor = visitor;

    model = new QStandardItemModel();
    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(model);
    ui->list->setModel(proxy);

    connect(ui->cmdSend, SIGNAL(pressed()), SLOT(sendMessage()));
    connect(ui->txtMessage, SIGNAL(sendMessage()), SLOT(sendMessage()));

    ui->Details->setVisitor(_visitor);
    ui->Cobrowse->setVisitor(_visitor);
}

VisitorChatView::~VisitorChatView()
{
    delete ui;
}

Visitor* VisitorChatView::visitor()
{
    return _visitor;
}

void VisitorChatView::messageReceived(QXmppMessage message)
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
        QStandardItem *item = new QStandardItem(message.body());
        model->appendRow(item);
        ui->list->scrollToBottom();
    }
    //ui->list->setIndexWidget(item->index(), new QPushButton("test button"));
}

void VisitorChatView::sendMessage()
{
    QString text = ui->txtMessage->toPlainText();
    ui->txtMessage->clear();
    QStandardItem *item = new QStandardItem(text);
    model->appendRow(item);
    ui->list->scrollToBottom();

    Core::network()->client->sendMessage(_visitor->Jid, text);
}
