#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "onlinestateselector.h"
#include "menubutton.h"
#include <QPixmap>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    MenuButton *w;

    w = new MenuButton(QPixmap(":/Images/MainMenu/colored/RU.png"), QString("test"));
    ui->horizontalLayout->insertWidget(1, w);
}

MainMenu::~MainMenu()
{
    delete ui;
}
