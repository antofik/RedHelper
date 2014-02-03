#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "core.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    LoginWindow *loginWindow = new LoginWindow(this);
    loginWindow->setWindowFlags(Qt::Drawer);
    loginWindow->setWindowModality(Qt::WindowModal);
    loginWindow->show();

    ui->setupUi(this);

    connect(Core::network(), SIGNAL(StateChanged()), SLOT(networkStateChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::networkStateChanged()
{
    Network *network;
    network = Core::network();
    if (network->isConnected())
    {
        ui->statusBar->showMessage(tr("Connected"));
    }
    else if (Core::network()->isConnecting())
    {
        ui->statusBar->showMessage(tr("Connecting"));
    }
    else
    {
        ui->statusBar->showMessage(tr("Disconnected"));
    }
}
