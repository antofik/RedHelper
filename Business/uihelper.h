#ifndef UIHELPER_H
#define UIHELPER_H

#include <QObject>

class UIHelper : public QObject
{
    Q_OBJECT
public:
    explicit UIHelper(QObject *parent = 0);

signals:
    void openChat(QString id, bool activate);

    void createTab(QString tabId);
    void activateTab(QString tabId);
    void closeTab(QString tabId);
    void setTabContent(QString tabId, QWidget* widget);
    void setTabName(QString tabId, QString name);

public slots:

};

#endif // UIHELPER_H
