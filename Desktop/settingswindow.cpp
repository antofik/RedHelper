#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->cmdSave, SIGNAL(clicked()), SLOT(close()));
    connect(ui->list, SIGNAL(currentRowChanged(int)), ui->stack, SLOT(setCurrentIndex(int)));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
