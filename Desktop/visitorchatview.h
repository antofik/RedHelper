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
#include "containers.h"
#include <QMenu>

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

private slots:
    void sendMessage();
    void currentTagChanged(int tabId);
    void seizeClicked();
    void redirectClicked();
    void doRedirect(QAction* action);
    void updateOperatorList();
    void visitorModified();

private:
    Ui::VisitorChatView *ui;
    Visitor *_visitor;
    QMenu *popupRedirect;

    void prepare(BaseNotification *notification);
};

#endif // VISITORCHATVIEW_H
