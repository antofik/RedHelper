#include "visitorchatview.h"
#include "ui_visitorchatview.h"
#include "QXmppMessage.h"
#include "core.h"
#include <QMessageBox>
#include "redirectwindow.h"

VisitorChatView::VisitorChatView(Visitor *visitor) : QWidget(0), ui(new Ui::VisitorChatView)
{
    enter
    ui->setupUi(this);
    _visitor = visitor;

    connect(ui->cmdSend, SIGNAL(pressed()), SLOT(sendMessage()));
    connect(ui->txtMessage, SIGNAL(sendMessage()), SLOT(sendMessage()));
    connect(ui->tabDetails, SIGNAL(currentChanged(int)), SLOT(currentTagChanged(int)));
    connect(ui->cmdRedirect, SIGNAL(clicked()), SLOT(redirectClicked()));
    connect(ui->cmdSeize, SIGNAL(clicked()), SLOT(seizeClicked()));
    connect(Core::operators(), SIGNAL(updated()), SLOT(updateOperatorList()));

    popupRedirect = new QMenu(ui->cmdRedirect);
    popupRedirect->setStyleSheet("QMenu{ menu-scrollable: 1; }");
    connect(popupRedirect, SIGNAL(triggered(QAction*)), SLOT(doRedirect(QAction*)));
    updateOperatorList();

    connect(_visitor, SIGNAL(modified()), SLOT(visitorModified()));

    ui->chat->setVisitor(_visitor);
    ui->Details->setVisitor(_visitor);

    visitorModified();
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

void VisitorChatView::seizeClicked()
{
    QXmppIq iq;
    QXmppElement query;
    query.setTagName("query");
    query.setAttribute("xmlns", "consultant:seizevisitor");
    query.setValue(_visitor->CurrentOperator);
    iq.setTo(_visitor->Jid.replace("visitor.", ""));
    iq.setExtensions(QXmppElementList() << query);
    //iq.setId(_visitor->Id);
    Core::network()->client->sendPacket(iq);
    emit ui->chat->seize(tr("Visitor is transferred to you"));
}

void VisitorChatView::redirectClicked()
{
    Core::operators()->update();
    popupRedirect->move(ui->cmdRedirect->mapToGlobal(QPoint(0, -popupRedirect->height())));
    popupRedirect->show();
}

void VisitorChatView::doRedirect(QAction *action)
{
    QString login = action->data().toString();
    RedirectWindow w(login);
    if (w.exec() != QDialog::Accepted) return;
    _visitor->redirect(login);
    Core::network()->redirectVisitorTo(_visitor, login, w.message());
    ui->chat->startRedirect(login, tr("Visitor was redirected to %1 with message %2").arg(login, w.message()));
}

void VisitorChatView::updateOperatorList()
{
    qDebug() << "updating list of operators" << Core::operators()->items()->count();
    popupRedirect->clear();
    QVector<Operator*> *os = Core::operators()->items();
    for(int i=0;i<os->count();i++)
    {
        Operator *o = os->at(i);
        if (o->Login == Core::network()->User) continue;

        QAction *action = new QAction(o->Name, popupRedirect);
        action->setData(o->Login);
        if (o->State == "online")
        {
            action->setIcon(QIcon(":/Images/Statuses/online16.png"));
        }
        else if (o->State == "dnd")
        {
            action->setIcon(QIcon(":/Images/Statuses/2ndline16.png"));
        }
        else if (o->State == "away")
        {
            action->setIcon(QIcon(":/Images/Statuses/away16.png"));
            action->setEnabled(false);
        }
        else if (o->State == "offline")
        {
            action->setIcon(QIcon(":/Images/Statuses/offline16.png"));
            action->setEnabled(false);
        }

        popupRedirect->addAction(action);
    }

    popupRedirect->move(ui->cmdRedirect->mapToGlobal(QPoint(0, -popupRedirect->height())));
}

void VisitorChatView::visitorModified()
{
    if (_visitor->ChatState == "chat")
    {
        ui->txtMessage->setEnabled(true);
        ui->cmdSend->setEnabled(true);
        ui->cmdRedirect->setEnabled(true);
        ui->cmdSeize->setEnabled(false);
    }
    else if (_visitor->ChatState == "browse")
    {
        ui->txtMessage->setEnabled(true);
        ui->cmdSend->setEnabled(true);
        ui->cmdRedirect->setEnabled(false);
        ui->cmdSeize->setEnabled(true);
    }
    else if (_visitor->ChatState == "busy")
    {
        ui->txtMessage->setEnabled(false);
        ui->cmdSend->setEnabled(false);
        ui->cmdRedirect->setEnabled(false);
        ui->cmdSeize->setEnabled(true);
    }
    else if (_visitor->ChatState == "offline")
    {
        ui->txtMessage->setEnabled(true);
        ui->cmdSend->setEnabled(true);
        ui->cmdRedirect->setEnabled(false);
        ui->cmdSeize->setEnabled(false);
    }
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

    Core::network()->sendMessage(_visitor->Jid, text);
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
