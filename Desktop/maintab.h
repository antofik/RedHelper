#ifndef MAINTAB_H
#define MAINTAB_H

#include <Qt>
#include <QWidget>
#include "visitorlistview.h"
#include "visitorchatview.h"
#include "core.h"
#include "visitor.h"

namespace Ui {
class MainTab;
}

class MainTab : public QWidget
{
    Q_OBJECT

public:
    explicit MainTab(QWidget *parent = 0);
    ~MainTab();

private slots:
    VisitorChatView* openChat(QString id, bool activate);
    void tabCloseRequested(int index);

    void messageReceived(TextNotification *message);
    void typingReceived(TypingNotification *message);
    void openChatByNotification(BaseNotification *message);

private:
    Ui::MainTab *ui;
    VisitorListView *visitorListView;
    QMap<QString, VisitorChatView*> *chats;
};

#endif // MAINTAB_H
