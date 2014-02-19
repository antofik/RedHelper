#include "bugreportwindow.h"
#include "ui_bugreportwindow.h"

BugReportWindow::BugReportWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BugReportWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->cmdCancel, SIGNAL(clicked()), SLOT(close()));
    connect(ui->cmdSend, SIGNAL(clicked()), SLOT(sendReport()));
}

BugReportWindow::~BugReportWindow()
{
    delete ui;
}

void BugReportWindow::sendReport()
{
    //todo send report
    close();
}
