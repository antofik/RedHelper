#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QCloseEvent>
#include "core.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    enter
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->control, SIGNAL(hideWindow()), SLOT(close()));
    leave
}

LoginWindow::~LoginWindow()
{
    enter
    delete ui->control;
    delete ui;
    leave
}

void LoginWindow::closeEvent(QCloseEvent *e)
{
    enter
    emit Core::ui()->loginWindowClosed();
    leave
}
