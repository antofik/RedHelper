#ifndef CHATCONTROL_H
#define CHATCONTROL_H

#include <QWidget>
#include "chatobject.h"
#include "QXmppMessage.h"
#include "containers.h"

namespace Ui {
class ChatControl;
}

class ChatControl : public QWidget
{
    Q_OBJECT

public:
    explicit ChatControl(QWidget *parent = 0);
    ~ChatControl();
    void setVisitor(Visitor* visitor);

    QSize sizeHint() const;

public slots:
    void messageReceived(TextNotification *message);
    void startRedirect(QString name, QString message);
    void seize(QString message);

private slots:
    void loadFinished(bool ok);
    void javaScriptWindowObjectCleared();
    void historyLoaded(QString visitorId, QVector<BaseNotification*>* notifications);    
    void typingReceived(TypingNotification *message);
    void redirectReceived(RedirectNotification *message);

private:
    Ui::ChatControl *ui;
    ChatObject *chat;
    Visitor* _visitor;

    bool isHistoryLoaded;
    void loadHistoryToChat();
};

#endif // CHATCONTROL_H
