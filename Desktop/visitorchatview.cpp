#include "visitorchatview.h"
#include "ui_visitorchatview.h"

VisitorChatView::VisitorChatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorChatView)
{
    ui->setupUi(this);
}

VisitorChatView::~VisitorChatView()
{
    delete ui;
}
