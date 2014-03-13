#ifndef REDIRECTWINDOW_H
#define REDIRECTWINDOW_H

#include <QDialog>

namespace Ui {
class RedirectWindow;
}

class RedirectWindow : public QDialog
{
    Q_OBJECT

public:
    RedirectWindow(QString login, QWidget *parent = 0);
    ~RedirectWindow();
    QString message();

private:
    Ui::RedirectWindow *ui;
};

#endif // REDIRECTWINDOW_H
