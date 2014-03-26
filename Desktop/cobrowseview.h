#ifndef COBROWSEVIEW_H
#define COBROWSEVIEW_H

#include <QWidget>
#include <Qt>
#include <QtCore>
#include "visitor.h"
#include "cobrowseobject.h"
#include <cobrowsenotification.h>
#include <mousenotification.h>
#include <QWebInspector>

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
    void stop();

private slots:
    void loadFinished(bool ok);
    void javaScriptWindowObjectCleared();
    void cobrowseReceived(CobrowseNotification* message);
    void mouseReceived(MouseNotification* message);

private:
    Ui::CobrowseView *ui;
    Visitor *_visitor;
    CobrowseObject *rhDesktop;
    QWebInspector *inspector;

    QVariant execute(QString script);
};

#endif // COBROWSEVIEW_H
