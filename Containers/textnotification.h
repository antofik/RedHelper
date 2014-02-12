#ifndef TEXTNOTIFICATION_H
#define TEXTNOTIFICATION_H

#include "basenotification.h"

class TextNotification : public BaseNotification
{
    Q_OBJECT

public:
    explicit TextNotification(QObject *parent = 0);

    QString Text;

signals:

public slots:

};

#endif // TEXTNOTIFICATION_H
