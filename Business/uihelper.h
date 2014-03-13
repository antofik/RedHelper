#ifndef UIHELPER_H
#define UIHELPER_H

#include <QObject>
#include <QWidget>

class UIHelper : public QObject
{
    Q_OBJECT
public:
    explicit UIHelper(QObject *parent = 0);
    bool isActive();
    void playSound();
    void flash();
    void stopFlash();

    WId mainWindowHandle;

signals:
    void openChat(QString id, bool activate);

    void createTab(QString tabId, bool closable);
    void activateTab(QString tabId);
    void closeTab(QString tabId);
    void setTabContent(QString tabId, QWidget* widget);
    void setTabName(QString tabId, QString name);    
    void setTabIcon(QString tabId, QString imagePath);
    void highlight(QString tabId);

    void showMainWindow();
    void loginWindowClosed();
    void updateOnlineCount();
    void showLoginWindow(bool);

    void update();

public slots:
    void exit();

private slots:
    void onUpdate();

};

#endif // UIHELPER_H
