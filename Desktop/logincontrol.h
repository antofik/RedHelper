#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H

#include <QWidget>

namespace Ui {
class LoginControl;
}

class LoginControl : public QWidget
{
    Q_OBJECT

public:
    explicit LoginControl(QWidget *parent = 0);
    ~LoginControl();

private slots:
    void login();
    void networkStateChanged();

signals:
    void hideWindow();

private:
    Ui::LoginControl *ui;
};

#endif // LOGINCONTROL_H
