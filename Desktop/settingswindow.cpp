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

    QSettings settings;
    ui->chkEnableSound_2->setChecked(settings.value("enableSounds", true).toBool());

    leave
}

SettingsWindow::~SettingsWindow()
{
    enter
    QSettings settings;
    settings.setValue("enableSounds", ui->chkEnableSound_2->isChecked());
    settings.sync();

    delete ui;
    leave
}
