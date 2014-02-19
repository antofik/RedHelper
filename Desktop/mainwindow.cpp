#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "core.h"
#include "onlinestateindicator.h"
#include <QPushButton>
#include "diagnosticswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(Core::ui(), SIGNAL(showMainWindow()), SLOT(show()));
    connect(Core::ui(), SIGNAL(loginWindowClosed()), SLOT(loginWindowClosed()));

#if WIN32
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->setWindowFlags(Qt::Dialog);
#else
    LoginWindow *loginWindow = new LoginWindow(this);
    loginWindow->setWindowFlags(Qt::Drawer);
    loginWindow->setWindowModality(Qt::WindowModal);
#endif
    loginWindow->show();

    connect(Core::network(), SIGNAL(stateChanged()), SLOT(networkStateChanged()));

    QPushButton *logButton = new QPushButton(tr("Diagnostics"));
    logButton->setFlat(true);
    connect(logButton, SIGNAL(clicked()), SLOT(diagnostics()));
    ui->statusBar->addPermanentWidget(logButton);
    OnlineStateIndicator *indicator = new OnlineStateIndicator();
    indicator->setFixedWidth(24);
    ui->statusBar->addPermanentWidget(indicator);
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
        //show();
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

void MainWindow::loginWindowClosed()
{
    if (this->isVisible()) return;
    this->close();
}

void MainWindow::diagnostics()
{
    DiagnosticsWindow *window = new DiagnosticsWindow();
    window->show();
}
