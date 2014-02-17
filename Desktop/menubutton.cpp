#include "menubutton.h"
#include "ui_menubutton.h"

MenuButton::MenuButton(QPixmap icon, QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuButton)
{
    ui->setupUi(this);    
    ui->image->setPixmap(icon);
    ui->text->setText(text);
}

MenuButton::~MenuButton()
{
    delete ui;
}

void MenuButton::mousePressEvent(QMouseEvent *e)
{
    emit click();
}
