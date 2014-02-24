#include "tabbutton.h"
#include "ui_tabbutton.h"
#include "core.h"

TabButton::TabButton(QString tabId, bool closable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabButton)
{
    enter
    _tabId = tabId;
    ui->setupUi(this);

    connect(ui->cmdClose, SIGNAL(clicked()), SLOT(closeClicked()));

    if (!closable)
        ui->cmdClose->hide();
    leave
}

TabButton::~TabButton()
{
    enter
    delete ui;
    leave
}

void TabButton::mousePressEvent (QMouseEvent *event)
{
    enter
    emit Core::ui()->activateTab(_tabId);
    leave
}

void TabButton::closeClicked()
{
    enter
    emit Core::ui()->closeTab(_tabId);
    leave
}

void TabButton::setIcon(QString imagePath)
{
    ui->image->setPixmap(QPixmap(imagePath));
}

void TabButton::select()
{
    enter
    setSelected(true);
    setStyleSheet(styleSheet());
    leave
}

void TabButton::unselect()
{
    enter
    setSelected(false);
    setStyleSheet(styleSheet());
    leave
}

void TabButton::highlight()
{
    enter
    if (!_isSelected)
    {
        setHighlighted(true);
        setStyleSheet(styleSheet());
    }
    leave
}

bool TabButton::isSelected()
{    
    return _isSelected;
}

void TabButton::setSelected(bool value)
{
    enter
    _isSelected = value;
    ui->panel->setProperty("selected", value);
    setHighlighted(false);
    leave
}

void TabButton::setHighlighted(bool value)
{
    enter
    ui->panel->setProperty("highlighted", value);
    leave
}

void TabButton::setText(QString text)
{
    enter
    ui->label->setText(text);
    leave
}
