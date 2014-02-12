#ifndef MOUSENOTIFICATION_H
#define MOUSENOTIFICATION_H

#include "basenotification.h"

class MouseNotification : public BaseNotification
{
    Q_OBJECT
public:
    explicit MouseNotification(QObject *parent = 0);

    QString Data;

signals:

public slots:

};

#endif // MOUSENOTIFICATION_H
