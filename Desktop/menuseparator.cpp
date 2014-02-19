#include "menuseparator.h"
#include "ui_menuseparator.h"

MenuSeparator::MenuSeparator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuSeparator)
{
    ui->setupUi(this);
}

MenuSeparator::~MenuSeparator()
{
    delete ui;
}
