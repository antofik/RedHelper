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

private:
    Ui::DiagnosticsWindow *ui;
    QStandardItemModel *model;
};

#endif // DIAGNOSTICSWINDOW_H
