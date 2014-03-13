#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(bool enableAutologin, QWidget *parent = 0);
    ~LoginWindow();
    void closeEvent(QCloseEvent *e);

public slots:

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
