#include "tabbar.h"
#include "ui_tabbar.h"
#include "core.h"
#include <QSpacerItem>
#include <QWidgetList>
#include <QScrollBar>

TabBar::TabBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabBar)
{
    ui->setupUi(this);
    ui->cmdScrollLeft->hide();
    ui->cmdScrollRight->hide();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    ui->scrollContent->setLayout(layout);

    ui->cmdScrollLeft->hide();
    ui->cmdScrollRight->hide();
    ui->scroll->adjustSize();
    ui->scrollContent->adjustSize();
    updateScrollButtonsVisibility();

    connect(Core::ui(), SIGNAL(createTab(QString, bool)), SLOT(createTab(QString, bool)));
    connect(Core::ui(), SIGNAL(activateTab(QString)), SLOT(activateTab(QString)));
    connect(Core::ui(), SIGNAL(setTabName(QString,QString)), SLOT(setTabName(QString,QString)));
    connect(Core::ui(), SIGNAL(highlight(QString)), SLOT(highlight(QString)));
    connect(Core::ui(), SIGNAL(closeTab(QString)), SLOT(closeTab(QString)));
    connect(ui->cmdScrollLeft, SIGNAL(clicked()), SLOT(scrollLeft()));
    connect(ui->cmdScrollRight, SIGNAL(clicked()), SLOT(scrollRight()));

}

TabBar::~TabBar()
{
    delete ui;
}

void TabBar::resizeEvent ( QResizeEvent * event )
{
    updateScrollButtonsVisibility();
}

void TabBar::updateScrollButtonsVisibility()
{
    int contentWidth = ui->scrollContent->size().width();
    int viewportWidth = ui->scroll->viewport()->size().width();
    if (contentWidth>viewportWidth)
    {
        ui->cmdScrollLeft->show();
        ui->cmdScrollRight->show();

        QScrollBar *bar = ui->scroll->horizontalScrollBar();
        ui->cmdScrollLeft->setEnabled(bar->value() > bar->minimum());
        ui->cmdScrollRight->setEnabled(bar->value() < bar->maximum());
    }
    else
    {
        ui->cmdScrollLeft->hide();
        ui->cmdScrollRight->hide();
    }
}

void TabBar::scrollLeft()
{
    QScrollBar *bar = ui->scroll->horizontalScrollBar();
    int value = bar->value();
    bar->setValue(qMin(bar->minimum(), value - 10));
    updateScrollButtonsVisibility();
}

void TabBar::scrollRight()
{
    QScrollBar *bar = ui->scroll->horizontalScrollBar();
    int value = bar->value();
    bar->setValue(qMax(bar->maximum(), value + 10));
    updateScrollButtonsVisibility();
}

void TabBar::createTab(QString tabId, bool closable)
{
    TabButton *button = new TabButton(tabId, closable);
    tabs[tabId] = button;    
    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->scrollContent->layout());
    layout->insertWidget(tabs.count() > 1 ? 1 : 0, button);
    updateScrollButtonsVisibility();
}

void TabBar::activateTab(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    if (tabs.contains(activeTab))
    {
        tabs[activeTab]->unselect();
    }
    tabs[tabId]->select();
    activeTab = tabId;
    scrollTo(tabId);
}

void TabBar::setTabName(QString tabId, QString name)
{
    if (!tabs.contains(tabId)) return;
    tabs[tabId]->setText(name);
    updateScrollButtonsVisibility();
}

void TabBar::closeTab(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    TabButton *tab = tabs[tabId];
    delete tab;
    tabs.remove(tabId);
    if (activeTab == tabId) activeTab = "";
    updateScrollButtonsVisibility();
}

void TabBar::scrollTo(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    ui->scroll->ensureWidgetVisible(tabs[tabId]);
}

QSize TabBar::sizeHint() const
{
    QSize size;
    size.setHeight(10);
    return size;
}

void TabBar::highlight(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    tabs[tabId]->highlight();
}










































