#ifndef MAINTAB_H
#define MAINTAB_H

#include <Qt>
#include <QWidget>
#include "visitorlistview.h"
#include "visitorchatview.h"

namespace Ui {
class MainTab;
}

class MainTab : public QWidget
{
    Q_OBJECT

public:
    explicit MainTab(QWidget *parent = 0);
    ~MainTab();

private:
    Ui::MainTab *ui;
    VisitorListView *visitorListView;
    QMap<QString, VisitorChatView> *chats;
};

#endif // MAINTAB_H
