#ifndef COBROWSEVIEW_H
#define COBROWSEVIEW_H

#include <QWidget>
#include <Qt>
#include <QtCore>
#include "visitor.h"
#include "cobrowseobject.h"

namespace Ui {
class CobrowseView;
}

class CobrowseView : public QWidget
{
    Q_OBJECT

public:
    explicit CobrowseView(QWidget *parent = 0);
    ~CobrowseView();
    void setVisitor(Visitor *visitor);
    void cobrowseReceived(QXmppMessage message);
    void mouseReceived(QXmppMessage message);

private slots:
    void loadFinished(bool ok);

private:
    Ui::CobrowseView *ui;
    Visitor *_visitor;
    CobrowseObject *rhDesktop;

    QVariant execute(QString script);
};

#endif // COBROWSEVIEW_H
