#include "tabbutton.h"
#include "ui_tabbutton.h"
#include "core.h"

TabButton::TabButton(QString tabId, bool closable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabButton)
{
    _tabId = tabId;
    ui->setupUi(this);

    connect(ui->cmdClose, SIGNAL(clicked()), SLOT(closeClicked()));

    if (!closable)
        ui->cmdClose->hide();
}

TabButton::~TabButton()
{
    delete ui;
}

void TabButton::mousePressEvent (QMouseEvent *event)
{
    emit Core::ui()->activateTab(_tabId);
}

void TabButton::closeClicked()
{
    emit Core::ui()->closeTab(_tabId);
}

void TabButton::select()
{
    setSelected(true);
    setStyleSheet(styleSheet());
}

void TabButton::unselect()
{
    setSelected(false);
    setStyleSheet(styleSheet());
}

void TabButton::highlight()
{
    if (_isSelected) return;
    setHighlighted(true);
    setStyleSheet(styleSheet());
}

bool TabButton::isSelected()
{
    return _isSelected;
}

void TabButton::setSelected(bool value)
{
    _isSelected = value;
    ui->panel->setProperty("selected", value);
    setHighlighted(false);
}

void TabButton::setHighlighted(bool value)
{
    ui->panel->setProperty("highlighted", value);
}

void TabButton::setText(QString text)
{
    ui->label->setText(text);
}
