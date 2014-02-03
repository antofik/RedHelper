#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->control, SIGNAL(hideWindow()), SLOT(hide()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
