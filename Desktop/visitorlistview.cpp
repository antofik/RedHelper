#include "visitorlistview.h"
#include "ui_visitorlistview.h"
#include "core.h"
#include "visitorupdater.h"
#include "visitor.h"
#include <QVariant>
#include "groupdelegate.h"

VisitorListView::VisitorListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorListView)
{
    ui->setupUi(this);

    model = new QStandardItemModel();
    QStringList header;

    QString headerLabels = "Name;Id;Visits;Pages;Time on site;Сity;Os;Browser;Ip;Current operator;Current url";
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

    ui->list->setColumnHidden(1, true);

    online = new QStandardItem(tr("Online"));
    browsing = new QStandardItem(tr("Browsing"));
    busy = new QStandardItem(tr("Busy"));
    //ui->list->set
    online->setIcon(QIcon(":/Images/Visitors/icon_plus.png"));
    model->setItem(0, 0, online);
    model->setItem(0, 1, new QStandardItem("online"));
    model->setItem(1, 0, browsing);
    model->setItem(1, 1, new QStandardItem("browsing"));
    model->setItem(2, 0, busy);
    model->setItem(2, 1, new QStandardItem("busy"));
    ui->list->setItemsExpandable(true);
    ui->list->setExpanded(online->index(), true);
    ui->list->setExpanded(browsing->index(), true);
    ui->list->setEditTriggers(QTreeView::NoEditTriggers);

    GroupDelegate *groupDelegate = new GroupDelegate(ui->list);
    ui->list->setItemDelegate(groupDelegate);

    connect(Core::visitors(), SIGNAL(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)), SLOT(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)));
    connect(ui->list, SIGNAL(doubleClicked(QModelIndex)), SLOT(doubleClicked(QModelIndex)));
    connect(ui->list, SIGNAL(clicked(QModelIndex)), SLOT(clicked(QModelIndex)));
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
        if (v->ChatState=="chat")
            online->appendRow(items);
        else if (v->ChatState=="busy")
            busy->appendRow(items);
        else if (v->ChatState=="browse")
            browsing->appendRow(items);
    }

    for (int i=0;i<modified.count();i++)
    {
        QString id = modified.at(i);
        Visitor *v = Core::visitors()->visitorById(id);
        if (!v) continue;
        QList<QStandardItem*> rows = model->findItems(id, Qt::MatchExactly, 1);
        if (rows.count()==1)
        {
            QModelIndex index = model->indexFromItem(rows.at(0));
            int row = index.row();
            QList<QStandardItem*> items = model->takeRow(row);
            DisplayVisitor(v, items);
            if (v->ChatState=="online")
                online->insertRow(row, items);
            else if (v->ChatState=="busy")
                busy->insertRow(row, items);
            else if (v->ChatState=="browsing")
                browsing->insertRow(row, items);
        }
    }

    for (int i=0;i<deleted.count();i++)
    {
        QString id = deleted.at(i);
        QList<QStandardItem*> rows = model->findItems(id, Qt::MatchExactly, 1);
        if (rows.count()==1)
        {
            int row = rows.at(0)->row();
            model->removeRow(row);
        }
    }
}

void VisitorListView::DisplayVisitor(Visitor *v, QList<QStandardItem*> items)
{
    int i = 0;
    //items.at(i++)->setText(v->ChatState);

    items.at(i)->setText(v->DisplayName());
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/cobrowse_icon.png"));

    items.at(i++)->setText(v->Id);

    items.at(i)->setText(v->Visits);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/pages.png"));

    items.at(i)->setText(v->ViewedPages);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/view.png"));

    items.at(i)->setText(v->TimeOnSite.toString("hh:mm:ss"));
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/time.png"));

    items.at(i)->setText(v->Country_ru);
    items.at(i++)->setIcon(QIcon(":/Images/Countries/" + v->CountryCode.toLower() + ".png"));

    items.at(i)->setText(v->Os);
    items.at(i++)->setIcon(QIcon(":/Images/Os/" + v->OsIcon().trimmed() + ".png"));

    items.at(i)->setText(v->BrowserName);
    items.at(i++)->setIcon(QIcon(":/Images/Browsers/" + v->BrowserIcon() + ".png"));

    items.at(i++)->setText(v->Ip);
    items.at(i++)->setText(v->CurrentOperator);
    items.at(i++)->setText(v->CurrentUrl);
    //ui->list->setItemDelegateForColumn(10, urlDelegate);
}

void VisitorListView::doubleClicked(QModelIndex index)
{
    if (!index.parent().isValid()) return;

    QString id = index.data(Qt::UserRole).toString();
    emit Core::ui()->openChat(id, true);
}

void VisitorListView::clicked(QModelIndex index)
{
    if (index.parent().isValid())
    {
        //todo hyperlinks
    }
    else
    {
        ui->list->setExpanded(index, !ui->list->isExpanded(index));
    }
}



















