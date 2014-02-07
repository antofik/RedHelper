#include "visitorlistview.h"
#include "ui_visitorlistview.h"
#include "core.h"
#include "visitorupdater.h"
#include "visitor.h"
#include <QVariant>

VisitorListView::VisitorListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorListView)
{
    ui->setupUi(this);

    model = new QStandardItemModel();
    QStringList header;

    QString headerLabels = "Id;Name;Visits;Viewed pages;Time on site;city;Os;Browser;Ip;Current operator;Current url";
    QStringList rawHeader = headerLabels.split(";");
    for (int i=0;i<rawHeader.count();i++)
    {
        QString rawName = rawHeader.at(i);
        QString name = QObject::tr(rawName.toUtf8());
        header.append(name);
    }
    model->setHorizontalHeaderLabels(header);
    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(model);
    ui->list->setModel(proxy);

    ui->list->setColumnHidden(0, true);
    ui->list->verticalHeader()->hide();
    //ui->list->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(Core::visitors(), SIGNAL(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)), SLOT(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)));
    connect(ui->list, SIGNAL(doubleClicked(QModelIndex)), SLOT(doubleClicked(QModelIndex)));
}

VisitorListView::~VisitorListView()
{
    delete ui;
}

void VisitorListView::VisitorChanged(const QVector<Visitor*> *added, const QStringList &modified, const QStringList &deleted)
{
    for(int i=0;i<added->count();i++)
    {
        Visitor *v = added->at(i);
        QList<QStandardItem*> items;
        for(int j=0;j<model->columnCount();j++)
        {
            QStandardItem *item = new QStandardItem();
            item->setEditable(false);
            item->setData(v->Id, Qt::UserRole);
            items.append(item);
        }
        DisplayVisitor(v, items);
        model->appendRow(items);
    }

    for (int i=0;i<modified.count();i++)
    {
        QString id = modified.at(i);
        Visitor *v = Core::visitors()->visitorById(id);
        QList<QStandardItem*> rows = model->findItems(id);
        if (rows.count()==1)
        {
            QModelIndex index = model->indexFromItem(rows.at(0));
            int row = index.row();
            QList<QStandardItem*> items = model->takeRow(row);
            DisplayVisitor(v, items);
            model->insertRow(row, items);
        }
    }
}

void VisitorListView::DisplayVisitor(Visitor *v, QList<QStandardItem*> items)
{
    items.at(0)->setText(v->Id);
    items.at(1)->setText(v->DisplayName());
    items.at(2)->setText(v->Visits);
    items.at(3)->setText(v->ViewedPages);
    items.at(4)->setText(v->TimeOnSite);
    items.at(5)->setText(v->Country_ru);
    items.at(6)->setText(v->Os);
    items.at(7)->setText(v->BrowserName);
    items.at(8)->setText(v->Ip);
    items.at(9)->setText(v->CurrentOperator);
    items.at(10)->setText(v->CurrentUrl);
}

void VisitorListView::doubleClicked(QModelIndex index)
{
    QStandardItem *item = model->item(index.row());
    QString id = item->text();
    emit Core::ui()->openChat(id, true);
}





















