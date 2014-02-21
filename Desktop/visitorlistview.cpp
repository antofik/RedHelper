#include "visitorlistview.h"
#include "ui_visitorlistview.h"
#include "core.h"
#include "visitorupdater.h"
#include "visitor.h"
#include <QVariant>
#include "groupdelegate.h"
#include <QDesktopServices>

VisitorListView::VisitorListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisitorListView)
{
    enter
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
    proxy->setSortRole(Qt::InitialSortOrderRole);
    ui->list->setModel(proxy);

    ui->list->setColumnHidden(1, true);

    online = new QStandardItem(tr("Online"));
    browsing = new QStandardItem(tr("Browsing"));
    busy = new QStandardItem(tr("Busy"));
    online->setIcon(QIcon(":/Images/Visitors/icon_plus.png"));
    model->setItem(0, 0, online);
    model->setItem(0, 1, new QStandardItem("online"));
    model->setItem(1, 0, browsing);
    model->setItem(1, 1, new QStandardItem("browsing"));
    model->setItem(2, 0, busy);
    model->setItem(2, 1, new QStandardItem("busy"));
    ui->list->expandAll();
    ui->list->setEditTriggers(QTreeView::NoEditTriggers);

    GroupDelegate *groupDelegate = new GroupDelegate(ui->list);
    ui->list->setItemDelegate(groupDelegate);

    connect(Core::visitors(), SIGNAL(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)), SLOT(VisitorChanged(const QVector<Visitor*>*,QStringList,QStringList)));
    connect(ui->list, SIGNAL(doubleClicked(QModelIndex)), SLOT(doubleClicked(QModelIndex)));
    connect(ui->list, SIGNAL(clicked(QModelIndex)), SLOT(clicked(QModelIndex)));

    ui->list->setColumnWidth(0, 130); //Name
    ui->list->setColumnWidth(2, 60); //Visits
    ui->list->setColumnWidth(3, 60); //Pages
    ui->list->setColumnWidth(4, 85); //Time on site
    ui->list->setColumnWidth(5, 85); //City
    ui->list->setColumnWidth(6, 80); //Os
    ui->list->setColumnWidth(7, 95); //Browser
    ui->list->setColumnWidth(8, 120); //Ip
    ui->list->setColumnWidth(9, 100); //Current operator
    ui->list->setColumnWidth(10, 280); //Current url
    leave
}

VisitorListView::~VisitorListView()
{
    enter
    delete ui;
    leave
}

void VisitorListView::VisitorChanged(const QVector<Visitor*> *added, const QStringList &modified, const QStringList &deleted)
{
    enter
    try
    {
        for(int i=0;i<added->count();i++)
        {
            Visitor *v = added->at(i);
            if (_rows.contains(v->Id))
            {
                continue;
            }

            QList<QStandardItem*> items;
            for(int j=0;j<model->columnCount();j++)
            {
                QStandardItem *item = new QStandardItem();
                item->setEditable(false);
                item->setData(v->Id, Qt::UserRole);
                items.append(item);
            }
            _rows[v->Id] = items;
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
            rows = _rows[id];
            if (rows.count()>0)
            {
                int row = rows.at(0)->row();
                if (row == -1) continue;
                QList<QStandardItem*> items = rows.at(0)->parent()->takeRow(row);
                DisplayVisitor(v, items);
                if (v->ChatState=="chat")
                    online->insertRow(row, items);
                else if (v->ChatState=="busy")
                    busy->insertRow(row, items);
                else if (v->ChatState=="browse")
                    browsing->insertRow(row, items);
                else {
                    qDebug() << "Failed to add visitor with chatstate" << v->ChatState;
                }
            }
        }

        for (int i=0;i<deleted.count();i++)
        {
            QString id = deleted.at(i);
            if (!_rows.contains(id)) continue;
            QList<QStandardItem*> rows = _rows[id];
            _rows.remove(id);
            if (rows.count() > 0 && rows.at(0)->parent())
            {
                rows.at(0)->parent()->removeRow(rows.at(0)->row());
            }
        }
    }
    catch(std::exception& e)
    {
        qDebug() << "Error!" << e.what();
    }
    catch(...)
    {
        qDebug() << "Unknown error!";
    }
    leave
}

void VisitorListView::DisplayVisitor(Visitor *v, QList<QStandardItem*> items)
{
    enter
    int i = 0;
    //items.at(i++)->setText(v->ChatState);

    items.at(i)->setText("#" + v->DisplayName());
    items.at(i)->setToolTip(v->DisplayName(true));

    items.at(i)->setData(v->DisplayName(), Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/cobrowse_icon.png"));

    items.at(i++)->setText(v->Id);

    items.at(i)->setText(v->Visits);
    items.at(i)->setToolTip(v->Visits);
    items.at(i)->setData(v->Visits.toInt(), Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/pages.png"));

    items.at(i)->setText(v->ViewedPages);
    items.at(i)->setData(v->ViewedPages.toInt(), Qt::InitialSortOrderRole);
    items.at(i)->setToolTip(v->ViewedPages);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/view.png"));

    items.at(i)->setText(v->TimeOnSite.toString("hh:mm:ss"));
    items.at(i)->setToolTip(v->TimeOnSite.toString("hh:mm:ss"));
    items.at(i)->setData(v->TimeOnSite, Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Visitors/time.png"));

    items.at(i)->setText(v->City_ru.isEmpty() ? v->Country_ru : v->City_ru);
    items.at(i)->setToolTip(v->Country_ru);
    items.at(i)->setData(v->Country_ru + "," + v->City_ru, Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Countries/" + v->CountryCode.toLower() + ".png"));

    items.at(i)->setText(v->Os);
    items.at(i)->setToolTip(v->Os);
    items.at(i)->setData(v->Os, Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Os/" + v->OsIcon().trimmed() + ".png"));

    items.at(i)->setText(v->BrowserName);
    items.at(i)->setToolTip(v->BrowserName);
    items.at(i)->setData(v->BrowserName, Qt::InitialSortOrderRole);
    items.at(i++)->setIcon(QIcon(":/Images/Browsers/" + v->BrowserIcon() + ".png"));

    items.at(i)->setText(v->Ip);
    items.at(i)->setData(v->Ip, Qt::InitialSortOrderRole);
    items.at(i++)->setToolTip(v->Ip);

    items.at(i)->setText(v->CurrentOperator);
    items.at(i)->setData(v->CurrentOperator, Qt::InitialSortOrderRole);
    items.at(i++)->setToolTip(v->CurrentOperator);

    items.at(i)->setText(v->CurrentUrl);
    items.at(i)->setData(v->CurrentUrl, Qt::InitialSortOrderRole);
    items.at(i++)->setToolTip(v->CurrentUrl);
    //ui->list->setItemDelegateForColumn(10, urlDelegate);
    leave
}

void VisitorListView::doubleClicked(QModelIndex index)
{
    enter
    if (!index.parent().isValid()) return;

    QString id = index.data(Qt::UserRole).toString();
    emit Core::ui()->openChat(id, true);
    leave
}

void VisitorListView::clicked(QModelIndex index)
{
    enter
    if (index.parent().isValid())
    {
        if (index.column() == 0)
        {
            QString id = index.data(Qt::UserRole).toString();
            Core::ui()->openChat(id, true);
        }
        else if (index.column() == 10)
        {
            QString url = index.data().toString();
            QDesktopServices::openUrl(url);
        }
    }
    else
    {
        ui->list->setExpanded(index, !ui->list->isExpanded(index));
    }
    leave
}



















