#include "redirectwindow.h"
#include "ui_redirectwindow.h"

RedirectWindow::RedirectWindow(QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RedirectWindow)
{
    ui->setupUi(this);
    ui->label->setText(tr("Redirect visitor to operator %1").arg(login));
    ui->txtMessage->setFocus();
}

RedirectWindow::~RedirectWindow()
{
    delete ui;
}

QString RedirectWindow::message()
{    
    return ui->txtMessage->toPlainText();
}
