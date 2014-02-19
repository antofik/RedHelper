#include "diagnosticswindow.h"
#include "ui_diagnosticswindow.h"
#include "log.h"
#include "logitem.h"

DiagnosticsWindow::DiagnosticsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagnosticsWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QString("Time;Message").split(";"));
    ui->list->setModel(model);
    //ui->list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->list->horizontalHeader()->setStretchLastSection(true);

    connect(Log::instance(), SIGNAL(added(LogItem*)), SLOT(added(LogItem*)));

    QStandardItem* item;
    QVector<LogItem*>* items = Log::items();
    for (int i=0;i<items->count();i++)
    {
        item = new QStandardItem(items->at(i)->time.toString("hh:mm:ss.zzz"));
        model->setItem(i, 0, item);

        item = new QStandardItem(items->at(i)->message);
        switch(items->at(i)->type)
        {
            case Log::Error:
                item->setIcon(QIcon(":/Images/Error.png"));
                break;
            case Log::Warning:
                item->setIcon(QIcon(":/Images/warning.png"));
                break;
            case Log::Info:
                item->setIcon(QIcon(":/Images/information.png"));
                break;
        }
        model->setItem(i, 1, item);
    }
}

DiagnosticsWindow::~DiagnosticsWindow()
{
    delete ui;
}

void DiagnosticsWindow::added(LogItem *log)
{
    QStandardItem* item;
    int i = model->rowCount();
    item = new QStandardItem(log->time.toString("hh:mm:ss.zzz"));
    model->setItem(i, 0, item);
    item = new QStandardItem(log->message);
    switch(log->type)
    {
        case Log::Error:
            item->setIcon(QIcon(":/Images/Error.png"));
            break;
        case Log::Warning:
            item->setIcon(QIcon(":/Images/warning.png"));
            break;
        case Log::Info:
            item->setIcon(QIcon(":/Images/information.png"));
            break;
    }
    model->setItem(i, 1, item);
}
