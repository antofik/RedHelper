#ifndef CHATCONTROL_H
#define CHATCONTROL_H

#include <QWidget>
#include "chatobject.h"

namespace Ui {
class ChatControl;
}

class ChatControl : public QWidget
{
    Q_OBJECT

public:
    explicit ChatControl(QWidget *parent = 0);
    ~ChatControl();

    QSize sizeHint() const;

private:
    Ui::ChatControl *ui;
    ChatObject *chat;
};

#endif // CHATCONTROL_H
