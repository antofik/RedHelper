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
    enter
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
    connect(Core::ui(), SIGNAL(setTabIcon(QString,QString)), SLOT(setTabIcon(QString,QString)));
    connect(Core::ui(), SIGNAL(highlight(QString)), SLOT(highlight(QString)));
    connect(Core::ui(), SIGNAL(closeTab(QString)), SLOT(closeTab(QString)));
    connect(ui->cmdScrollLeft, SIGNAL(clicked()), SLOT(scrollLeft()));
    connect(ui->cmdScrollRight, SIGNAL(clicked()), SLOT(scrollRight()));
    leave
}

TabBar::~TabBar()
{
    enter
    delete ui;
    leave
}

void TabBar::resizeEvent ( QResizeEvent * event)
{
    enter
    updateScrollButtonsVisibility();
    leave
}

void TabBar::updateScrollButtonsVisibility()
{
    enter
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
    leave
}

void TabBar::scrollLeft()
{
    enter
    QScrollBar *bar = ui->scroll->horizontalScrollBar();
    int value = bar->value();
    bar->setValue(qMin(bar->minimum(), value - 10));
    updateScrollButtonsVisibility();
    leave
}

void TabBar::scrollRight()
{
    enter
    QScrollBar *bar = ui->scroll->horizontalScrollBar();
    int value = bar->value();
    bar->setValue(qMax(bar->maximum(), value + 10));
    updateScrollButtonsVisibility();
    leave
}

void TabBar::createTab(QString tabId, bool closable)
{
    enter
    TabButton *button = new TabButton(tabId, closable);
    tabs[tabId] = button;    
    QHBoxLayout *layout = static_cast<QHBoxLayout*>(ui->scrollContent->layout());
    layout->insertWidget(tabs.count() > 1 ? 1 : 0, button);
    updateScrollButtonsVisibility();
    leave
}

void TabBar::activateTab(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;
    if (tabs.contains(activeTab))
    {
        tabs[activeTab]->unselect();
    }
    tabs[tabId]->select();
    activeTab = tabId;
    scrollTo(tabId);
    leave
}

void TabBar::setTabName(QString tabId, QString name)
{
    enter
    if (!tabs.contains(tabId)) return;
    tabs[tabId]->setText(name);
    updateScrollButtonsVisibility();
    leave
}

void TabBar::setTabIcon(QString tabId, QString imagePath)
{
    enter
    if (!tabs.contains(tabId)) return;
    tabs[tabId]->setIcon(imagePath);
    updateScrollButtonsVisibility();
    leave
}

void TabBar::closeTab(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;
    TabButton *tab = tabs[tabId];
    delete tab;
    tabs.remove(tabId);
    if (activeTab == tabId) activeTab = "";
    updateScrollButtonsVisibility();
    leave
}

void TabBar::scrollTo(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;
    ui->scroll->ensureWidgetVisible(tabs[tabId]);
    leave
}

QSize TabBar::sizeHint() const
{
    enter
    QSize size;
    size.setHeight(10);
    leave
    return size;    
}

void TabBar::highlight(QString tabId)
{
    enter
    if (!tabs.contains(tabId)) return;
    tabs[tabId]->highlight();
    leave
}










































