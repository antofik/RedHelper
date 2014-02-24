#include "menuseparator.h"
#include "ui_menuseparator.h"
#include "core.h"

MenuSeparator::MenuSeparator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuSeparator)
{
    enter
    ui->setupUi(this);
    leave
}

MenuSeparator::~MenuSeparator()
{
    enter
    delete ui;
    leave
}
