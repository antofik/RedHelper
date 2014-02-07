#ifndef VISITORCHATVIEW_H
#define VISITORCHATVIEW_H

#include <Qt>
#include <QtCore>
#include <QWidget>
#include "visitorchatview.h"
#include "visitor.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include "QXmppMessage.h"

namespace Ui {
class VisitorChatView;
}

class VisitorChatView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitorChatView(Visitor *visitor);
    ~VisitorChatView();
    Visitor* visitor();
    void messageReceived(QXmppMessage message);

private slots:
    void sendMessage();


private:
    Ui::VisitorChatView *ui;
    Visitor *_visitor;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxy;
};

#endif // VISITORCHATVIEW_H
