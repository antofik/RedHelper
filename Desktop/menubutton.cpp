#include "menubutton.h"
#include "ui_menubutton.h"
#include <QDebug>
#include "core.h"

MenuButton::MenuButton(QPixmap icon, QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuButton)
{
    enter
    ui->setupUi(this);    
    ui->text->setText(text);
    ui->image->setPixmap(icon);
    leave
}

MenuButton::~MenuButton()
{
    enter
    delete ui;
    leave
}

void MenuButton::mousePressEvent(QMouseEvent *e)
{
    enter
    ui->widget->setProperty("IsPressed", true);
    ui->widget->setStyleSheet(ui->widget->styleSheet());

    emit click();
    leave
}

void MenuButton::mouseReleaseEvent(QMouseEvent *e)
{
    enter
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
    leave
}

void MenuButton::leaveEvent(QEvent *e)
{
    enter
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
    leave
}

MenuButton* MenuButton::button(QPixmap icon, QString text, const QObject *context, char const* f)
{
    enter
    MenuButton *item = new MenuButton(icon, text);
    QObject::connect(item, SIGNAL(click()), context, f);
    leave
    return item;
}
