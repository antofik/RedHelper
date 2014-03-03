#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <QString>

class NotificationCenter //: NSUserNotificationCenterDelegate<NSObject>
{
public:
    explicit NotificationCenter();

    static NotificationCenter* instance();

    void showNotification(QString title, QString message);
};


#endif // NOTIFICATIONCENTER_H
