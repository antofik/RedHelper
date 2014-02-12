#ifndef TYPINGNOTIFICATION_H
#define TYPINGNOTIFICATION_H

#include "basenotification.h"

class TypingNotification : public BaseNotification
{
    Q_OBJECT
public:
    explicit TypingNotification(QObject *parent = 0);

    QString Text;

signals:

public slots:

};

#endif // TYPINGNOTIFICATION_H
