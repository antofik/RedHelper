#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H

#include <QWidget>
#include <Qt>
#include <QtCore>
#include "QXmppClient.h"

namespace Ui {
class LoginControl;
}

class LoginControl : public QWidget
{
    Q_OBJECT

public:
    explicit LoginControl(QWidget *parent = 0);
    ~LoginControl();
    void autologin();

private slots:
    void login();
    void cancel();
    void enableEditing(bool ok);
    void networkStateChanged();
    void xmppError(QXmppStanza::Error::Condition error);
    void socketError(QAbstractSocket::SocketError error);

signals:
    void hideWindow();

private:
    Ui::LoginControl *ui;
};

#endif // LOGINCONTROL_H
