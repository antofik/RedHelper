#ifndef BASENOTIFICATION_H
#define BASENOTIFICATION_H

#include <QObject>
#include <QDateTime>

class BaseNotification : public QObject
{
    Q_OBJECT

public:
    explicit BaseNotification(QObject* parent=0);

    QString From;
    QString To;
    QString Id;
    QDateTime Time;
    QString OperatorDisplayName;
    QString VisitorId;
    QString OperatorLogin;
    bool IsIncoming;
    bool IsOperatorToOperator;
    QString FromOperator;
    QString ToOperator;

signals:

public slots:

};

#endif // BASENOTIFICATION_H
