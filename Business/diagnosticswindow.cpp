#include "diagnosticswindow.h"
#include "ui_diagnosticswindow.h"
#include "log.h"
#include "logitem.h"
#include "core.h"
#include <Qt>
#include <QtCore>
#include <QtGui>
#include <QColor>

DiagnosticsWindow::DiagnosticsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagnosticsWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QString("Time;Message").split(";"));
    ui->list->setModel(model);
    ui->list->horizontalHeader()->setStretchLastSection(true);

    modelXmpp = new QStandardItemModel();
    ui->listXmpp->setModel(modelXmpp);

    connect(Log::instance(), SIGNAL(added(LogItem*)), SLOT(added(LogItem*)));

    QStandardItem* item;
    QVector<LogItem*>* items = Log::items();
    int j = 0;
    int x = 0;
    for (int i=0;i<items->count();i++)
    {
        if (items->at(i)->type == Log::Xmpp)
        {
            item = new QStandardItem(items->at(i)->message);
            item->setForeground(Qt::red);
            modelXmpp->setItem(x++, item);
            //item = new QStandardItem(items->at(i)->time.toString("hh:mm:ss.zzz"));
            //model->setItem(x++, item);
        }
        else
        {
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
                default:
                    continue;
            }
            model->setItem(j, 1, item);
            item = new QStandardItem(items->at(i)->time.toString("hh:mm:ss.zzz"));
            model->setItem(j++, 0, item);
        }
    }

    connect(Core::network(), SIGNAL(logMessage(QString,bool,bool,bool,bool)), SLOT(logMessage(QString,bool,bool,bool,bool)));
}

DiagnosticsWindow::~DiagnosticsWindow()
{
    delete ui;
}

void DiagnosticsWindow::added(LogItem *log)
{
    if (log->type == Log::Xmpp)
    {
        QStandardItem* item;
        int i = modelXmpp->rowCount();
        item = new QStandardItem(log->message);
        modelXmpp->setItem(i, item);
    }
    else
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
}

void DiagnosticsWindow::logMessage(QString stanza, bool isIncoming, bool isIq, bool isMessage, bool isOperatorToOperator)
{
    Log::xmpp(stanza, isIncoming, isIq, isMessage, isOperatorToOperator);
}
