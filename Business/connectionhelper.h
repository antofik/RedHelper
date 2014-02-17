#ifndef CONNECTIONHELPER_H
#define CONNECTIONHELPER_H

#include <QObject>

class ConnectionHelper : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHelper(QObject *parent = 0);

signals:

public slots:
    void doWork();

};

#endif // CONNECTIONHELPER_H
