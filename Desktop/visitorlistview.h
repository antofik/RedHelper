#ifndef VISITORLISTVIEW_H
#define VISITORLISTVIEW_H

#include <Qt>
#include <QtCore>
#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include "visitorlistview.h"
#include "visitor.h"
#include "visitorchatview.h"

namespace Ui {
class VisitorListView;
}

class VisitorListView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitorListView(QWidget *parent = 0);
    ~VisitorListView();
    void DisplayVisitor(Visitor *v, QList<QStandardItem*> items);
    void openChat(QString id, bool activate = false);

private slots:
    void VisitorChanged(const QVector<Visitor*> *added, const QStringList &modified, const QStringList &deleted);
    void doubleClicked(QModelIndex index);
    void clicked(QModelIndex index);

private:
    Ui::VisitorListView *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxy;    

    QStandardItem *online;
    QStandardItem *busy;
    QStandardItem *browsing;
};

#endif // VISITORLISTVIEW_H
