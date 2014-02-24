#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "core.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    enter
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->cmdSave, SIGNAL(clicked()), SLOT(close()));
    connect(ui->list, SIGNAL(currentRowChanged(int)), ui->stack, SLOT(setCurrentIndex(int)));
    leave
}

SettingsWindow::~SettingsWindow()
{
    enter
    delete ui;
    leave
}
