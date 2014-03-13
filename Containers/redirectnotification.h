#ifndef REDIRECTNOTIFICATION_H
#define REDIRECTNOTIFICATION_H

#include "basenotification.h"

class RedirectNotification : public BaseNotification
{
    Q_OBJECT
public:
    explicit RedirectNotification(QObject *parent = 0);

    QString Login;
    QString Message;

    enum Type{
        Redirect = 0,
        Notify = 1,
        Ok = 2,
        Fail = 3,
    };

    Type Type;

signals:

public slots:

};

#endif // REDIRECTNOTIFICATION_H
