#ifndef MEMORYCHECKER_H
#define MEMORYCHECKER_H

#include <QObject>

class MemoryChecker : public QObject
{
    Q_OBJECT
public:
    explicit MemoryChecker(QObject *parent = 0);
    static int GetMemoryUsage();

signals:

public slots:

};

#endif // MEMORYCHECKER_H
