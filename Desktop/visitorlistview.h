#ifndef VISITORLISTVIEW_H
#define VISITORLISTVIEW_H

#include <QWidget>

namespace Ui {
class VisitorListView;
}

class VisitorListView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitorListView(QWidget *parent = 0);
    ~VisitorListView();

private:
    Ui::VisitorListView *ui;
};

#endif // VISITORLISTVIEW_H
