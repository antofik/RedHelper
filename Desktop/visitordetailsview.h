#ifndef VISITORDETAILSVIEW_H
#define VISITORDETAILSVIEW_H

#include <QWidget>
#include <Qt>
#include <QtCore>
#include "visitor.h"
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class VisitorDetailsView;
}

class VisitorDetailsView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitorDetailsView(QWidget *parent = 0);
    ~VisitorDetailsView();
    void setVisitor(Visitor *visitor);

private slots:
    void showVisitor();

private:
    Ui::VisitorDetailsView *ui;
    Visitor *_visitor;
    QStandardItemModel model;
    void addRow(int &row, QString name, QString value);
};

#endif // VISITORDETAILSVIEW_H
