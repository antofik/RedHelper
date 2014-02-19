#include "visitordetailsview.h"
#include "ui_visitordetailsview.h"
#include <QHeaderView>

VisitorDetailsView::VisitorDetailsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorDetailsView)
{
    ui->setupUi(this);
    ui->list->horizontalHeader()->hide();
    ui->list->verticalHeader()->hide();
    ui->list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->list->setModel(&model);
}

VisitorDetailsView::~VisitorDetailsView()
{
    delete ui;
}

void VisitorDetailsView::setVisitor(Visitor *visitor)
{
    _visitor = visitor;
    connect(_visitor, SIGNAL(modified()), SLOT(showVisitor()));
    showVisitor();
}

void VisitorDetailsView::addRow(int &row, QString name, QString value)
{
    model.setItem(row, 0, new QStandardItem(name));
    model.setItem(row, 1, new QStandardItem(value));
    row++;
}

void VisitorDetailsView::showVisitor()
{
    QStandardItem *name;
    QStandardItem *value;
    int row = 0;

    addRow(row, tr("Name"), _visitor->DisplayName());
    addRow(row, tr("Country"), _visitor->Country_en);
    addRow(row, tr("City"), _visitor->City_en);
    addRow(row, tr("Organization"), _visitor->Organization);
    addRow(row, tr("IP"), _visitor->Ip);
    addRow(row, tr("Source"), _visitor->Referrer);
    addRow(row, tr("Current url"), _visitor->CurrentUrl);
    addRow(row, tr("Title"), _visitor->CurrentPageTitle);
    addRow(row, tr("Chat status"), _visitor->ChatState);
    addRow(row, tr("Invite status"), _visitor->InviteState);
    addRow(row, tr("Current operator"), _visitor->CurrentOperator);
    addRow(row, tr("Operating system"), _visitor->Os);
    addRow(row, tr("Browser"), _visitor->BrowserName);
    addRow(row, tr("Visits"), _visitor->Visits);
    addRow(row, tr("Viewed pages"), _visitor->ViewedPages);
    addRow(row, tr("Time on site"), _visitor->TimeOnSite.toString("hh:mm:ss"));
    addRow(row, tr("Trigger"), _visitor->Trigger);
}


