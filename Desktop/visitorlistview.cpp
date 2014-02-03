#include "visitorlistview.h"
#include "ui_visitorlistview.h"

VisitorListView::VisitorListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorListView)
{
    ui->setupUi(this);
}

VisitorListView::~VisitorListView()
{
    delete ui;
}
