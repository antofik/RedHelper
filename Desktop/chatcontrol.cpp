#include "chatcontrol.h"
#include "ui_chatcontrol.h"
#include <QWebView>
#include <QWebFrame>
#include <QDir>

ChatControl::ChatControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatControl)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui->setupUi(this);    

    qDebug() << qApp->applicationDirPath() + "/VisitorChat.html";
    ui->web->setUrl(QUrl::fromLocalFile(qApp->applicationDirPath() + "/VisitorChat.html"));

    chat = new ChatObject();
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhChat", chat);
}

ChatControl::~ChatControl()
{
    delete ui;
}

QSize ChatControl::sizeHint() const
{
    QSize size(400,-1);
    return size;
}
