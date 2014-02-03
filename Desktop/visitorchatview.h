#ifndef VISITORCHATVIEW_H
#define VISITORCHATVIEW_H

#include <QWidget>

namespace Ui {
class VisitorChatView;
}

class VisitorChatView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitorChatView(QWidget *parent = 0);
    ~VisitorChatView();

private:
    Ui::VisitorChatView *ui;
};

#endif // VISITORCHATVIEW_H
