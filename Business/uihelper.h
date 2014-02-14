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

    void createTab(QString tabId, bool closable);
    void activateTab(QString tabId);
    void closeTab(QString tabId);
    void setTabContent(QString tabId, QWidget* widget);
    void setTabName(QString tabId, QString name);
    void highlight(QString tabId);

    void update();

public slots:

private slots:
    void onUpdate();

};

#endif // UIHELPER_H
