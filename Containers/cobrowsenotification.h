#ifndef COBROWSENOTIFICATION_H
#define COBROWSENOTIFICATION_H

#include "basenotification.h"

class CobrowseNotification : public BaseNotification
{
    Q_OBJECT
public:
    explicit CobrowseNotification(QObject *parent = 0);

    QString Data;

signals:

public slots:

};

#endif // COBROWSENOTIFICATION_H
