#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::mousePressEvent(QMouseEvent *e)
{
    close();
}
