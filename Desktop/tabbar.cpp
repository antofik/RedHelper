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
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    ui->scrollContent->setLayout(layout);

    updateScrollButtonsVisibility();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    connect(Core::ui(), SIGNAL(createTab(QString)), SLOT(createTab(QString)));
    connect(Core::ui(), SIGNAL(activateTab(QString)), SLOT(activateTab(QString)));
    connect(Core::ui(), SIGNAL(setTabName(QString,QString)), SLOT(setTabName(QString,QString)));
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

void TabBar::createTab(QString tabId)
{
    TabButton *button = new TabButton(tabId);
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

    qDebug() << tabs[tabId]->sizeHint() << tabs[tabId]->size();
}

void TabBar::closeTab(QString tabId)
{
    if (!tabs.contains(tabId)) return;
    ui->scrollContent->layout()->removeWidget(tabs[tabId]);
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











































