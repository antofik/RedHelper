#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QCloseEvent>
#include "core.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->control, SIGNAL(hideWindow()), SLOT(close()));
}

LoginWindow::~LoginWindow()
{
    delete ui->control;
    delete ui;
}

void LoginWindow::closeEvent(QCloseEvent *e)
{
    emit Core::ui()->loginWindowClosed();
}
