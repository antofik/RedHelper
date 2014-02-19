#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "onlinestateselector.h"
#include "menubutton.h"
#include <QPixmap>
#include "menuseparator.h"
#include <QWebView>
#include "aboutwindow.h"
#include "bugreportwindow.h"
#include "settingswindow.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    int i = 1;
    ui->horizontalLayout->insertWidget(i++, new OnlineStateSelector());
    ui->horizontalLayout->insertWidget(i++, new MenuSeparator());
    ui->horizontalLayout->insertWidget(i++, MenuButton::button(QPixmap(":/Images/MainMenu/colored/settings.png"), tr("Settings"), this, SLOT(settings())));
    ui->horizontalLayout->insertWidget(i++, MenuButton::button(QPixmap(":/Images/MainMenu/colored/bugreport.png"), tr("Report"), this, SLOT(bugreport())));
    ui->horizontalLayout->insertWidget(i++, MenuButton::button(QPixmap(":/Images/MainMenu/colored/about.png"), tr("About"), this, SLOT(about())));
    ui->horizontalLayout->insertWidget(i++, new MenuSeparator());
    ui->horizontalLayout->insertWidget(i++, MenuButton::button(QPixmap(":/Images/MainMenu/colored/onlinehelp.png"), tr("Online help"), this, SLOT(onlinehelp())));
    ui->horizontalLayout->insertWidget(i++, new MenuSeparator());
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::settings()
{
    SettingsWindow *window = new SettingsWindow();
    window->setWindowFlags(Qt::Dialog);
    window->setWindowModality(Qt::ApplicationModal);
    window->setWindowTitle(tr("Settings"));
    window->show();
}

void MainMenu::bugreport()
{
    BugReportWindow *window = new BugReportWindow();
    window->setWindowFlags(Qt::Dialog);
    window->setWindowModality(Qt::ApplicationModal);
    window->setWindowTitle(tr("Bug report"));
    window->show();
}

void MainMenu::about()
{
    AboutWindow *window = new AboutWindow();
    window->setWindowFlags(Qt::Dialog);
    window->setWindowModality(Qt::ApplicationModal);
    window->setWindowTitle(tr("About"));
    window->show();
}

void MainMenu::onlinehelp()
{
    QWebView* view = new QWebView();
    view->resize(300, 400);
    view->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    view->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    view->setUrl(QUrl("http://web.redhelper.ru/chat/index.html?c=rhlp&standalone&desktop&qt"));
    view->setWindowFlags(Qt::Dialog);
    view->setWindowTitle(tr("Online help"));
    view->show();
}
