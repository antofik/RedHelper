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

    void messageReceived(TextNotification *message);
    void typingReceived(TypingNotification *message);
    void openChatByNotification(BaseNotification *message);

    void activateTab(QString tabId);
    void closeTab(QString tabId);
    void setTabContent(QString tabId, QWidget* widget);
    void updateOnlineCount();

private:
    Ui::MainTab *ui;
    VisitorListView *visitorListView;
    QMap<QString, VisitorChatView*> *chats;
    QMap<QString, QWidget*> tabs;
};

#endif // MAINTAB_H
