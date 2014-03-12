#ifndef DIAGNOSTICSWINDOW_H
#define DIAGNOSTICSWINDOW_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include  "logitem.h"

namespace Ui {
class DiagnosticsWindow;
}

class DiagnosticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DiagnosticsWindow(QWidget *parent = 0);
    ~DiagnosticsWindow();

private slots:
    void added(LogItem *item);
    void logMessage(QString stanza, bool isIncoming, bool isIq, bool isMessage, bool isOperatorToOperator);

private:
    Ui::DiagnosticsWindow *ui;
    QStandardItemModel *model;
    QStandardItemModel *modelXmpp;
};

#endif // DIAGNOSTICSWINDOW_H
