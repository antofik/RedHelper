#include "maintab.h"
#include "ui_maintab.h"

MainTab::MainTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTab)
{
    ui->setupUi(this);


    visitorListView = new VisitorListView();
    //add visitor tab
    ui->tab->addTab(visitorListView, tr("Visitors"));

    //hide close button of visitor list view
    QWidget *button = ui->tab->tabBar()->tabButton(0, QTabBar::RightSide);
    if (!button) button = ui->tab->tabBar()->tabButton(0, QTabBar::LeftSide);
    if (button) button->hide();
}

MainTab::~MainTab()
{
    delete ui;
}
