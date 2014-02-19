#include "menubutton.h"
#include "ui_menubutton.h"
#include <QDebug>

MenuButton::MenuButton(QPixmap icon, QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuButton)
{
    ui->setupUi(this);    
    ui->text->setText(text);
    ui->image->setPixmap(icon);
}

MenuButton::~MenuButton()
{
    delete ui;
}

void MenuButton::mousePressEvent(QMouseEvent *e)
{
    ui->widget->setProperty("IsPressed", true);
    ui->widget->setStyleSheet(ui->widget->styleSheet());

    emit click();
}

void MenuButton::mouseReleaseEvent(QMouseEvent *e)
{
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
}

void MenuButton::leaveEvent(QEvent *e)
{
    ui->widget->setProperty("IsPressed", false);
    ui->widget->setStyleSheet(ui->widget->styleSheet());
}

MenuButton* MenuButton::button(QPixmap icon, QString text, const QObject *context, char const* f)
{
    MenuButton *item = new MenuButton(icon, text);
    QObject::connect(item, SIGNAL(click()), context, f);
    return item;
}
