#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QMap>
#include "tabbutton.h"

namespace Ui {
class TabBar;
}

class TabBar : public QWidget
{
    Q_OBJECT

public:
    explicit TabBar(QWidget *parent = 0);
    ~TabBar();
    QSize sizeHint() const;
    void resizeEvent ( QResizeEvent * event );

private slots:
    void createTab(QString tabId);
    void activateTab(QString tabId);
    void closeTab(QString tabId);
    void setTabName(QString tabId, QString name);
    void scrollLeft();
    void scrollRight();

private:
    Ui::TabBar *ui;

    QMap<QString, TabButton*> tabs;
    QString activeTab;    

    void scrollTo(QString tabId);
    void updateScrollButtonsVisibility();
};

#endif // TABBAR_H
