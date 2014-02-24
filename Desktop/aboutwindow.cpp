#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include "core.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    enter
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    leave
}

AboutWindow::~AboutWindow()
{
    enter
    delete ui;
    leave
}

void AboutWindow::mousePressEvent(QMouseEvent *e)
{
    enter
    close();
    leave
}
