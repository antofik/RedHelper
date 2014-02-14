#include "onlinestateselector.h"
#include "ui_onlinestateselector.h"

OnlineStateSelector::OnlineStateSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineStateSelector)
{
    ui->setupUi(this);
}

OnlineStateSelector::~OnlineStateSelector()
{
    delete ui;
}
