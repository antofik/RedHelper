#include "onlinestatepopup.h"
#include "ui_onlinestatepopup.h"

OnlineStatePopup::OnlineStatePopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineStatePopup)
{
    ui->setupUi(this);
}

OnlineStatePopup::~OnlineStatePopup()
{
    delete ui;
}
