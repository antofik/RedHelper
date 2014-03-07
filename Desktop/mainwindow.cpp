#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "core.h"
#include "onlinestateindicator.h"
#include <QPushButton>
#include "diagnosticswindow.h"
#include "objectiveinitializer.h"

MainWindow::MainWindow(AutoUpdater* updater, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    enter    
    ui->setupUi(this);
    connect(Core::ui(), SIGNAL(showMainWindow()), SLOT(show()));
    connect(Core::ui(), SIGNAL(loginWindowClosed()), SLOT(loginWindowClosed()));
    connect(Core::ui(), SIGNAL(showLoginWindow()), SLOT(showLoginWindow()));
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(networkStateChanged()));

    QPushButton *logButton = new QPushButton(tr("Diagnostics"));
    logButton->setFlat(true);
    connect(logButton, SIGNAL(clicked()), SLOT(diagnostics()));
    ui->statusBar->addPermanentWidget(logButton);
    OnlineStateIndicator *indicator = new OnlineStateIndicator();
    indicator->setFixedWidth(24);
    ui->statusBar->addPermanentWidget(indicator);

    emit Core::ui()->showLoginWindow();

    if (updater)
    {
        updater->checkForUpdates();
    }

    ObjectiveInitializer::test(this);

    leave
}

MainWindow::~MainWindow()
{
    enter
    delete ui;
    leave
}

void MainWindow::showLoginWindow()
{
    enter
#if WIN32
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->setWindowFlags(Qt::Dialog);
#else
    LoginWindow *loginWindow = new LoginWindow(this);
    loginWindow->setWindowModality(Qt::WindowModal);
#endif
    loginWindow->show();
    leave
}

void MainWindow::showEvent(QShowEvent * event)
{
    Core::ui()->mainWindowHandle = effectiveWinId();
    Core::ui()->stopFlash();
}

void MainWindow::networkStateChanged()
{
    enter
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
    leave
}

void MainWindow::loginWindowClosed()
{
    enter
    if (this->isVisible()) return;
    this->close();    
    leave
}

void MainWindow::diagnostics()
{
    enter
    DiagnosticsWindow *window = new DiagnosticsWindow();
    window->show();
    leave
}
