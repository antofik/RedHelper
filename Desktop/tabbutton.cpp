#include "tabbutton.h"
#include "ui_tabbutton.h"
#include "core.h"

TabButton::TabButton(QString tabId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabButton)
{
    _tabId = tabId;
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumWidth(80);
    //ui->cmdClose->hide();
}

TabButton::~TabButton()
{
    delete ui;
}

void TabButton::mousePressEvent ( QMouseEvent *event)
{
    emit Core::ui()->activateTab(_tabId);
}

void TabButton::select()
{
    QString style = "#panel{background-color:#e0e0e0;border-style:solid;border-color:darkgray;border-width:1px;border-bottom-width:0px;border-top-left-radius:4px;border-top-right-radius:4px;}";
    setStyleSheet(style);
}

void TabButton::unselect()
{
    QString style = "#panel{background-color:#d0d0d0;border-style:solid;border-color:darkgray;border-width:1px;border-bottom-width:0px;border-top-left-radius:4px;border-top-right-radius:4px;}";
    setStyleSheet(style);
}

bool TabButton::isSelected()
{
    return _isSelected;
}

void TabButton::setSelected(bool value)
{
    _isSelected = value;
    setStyleSheet(styleSheet());
}

void TabButton::setText(QString text)
{
    ui->label->setText(text);
}
