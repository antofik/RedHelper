#ifndef MEMORYCHECKER_H
#define MEMORYCHECKER_H

#include <QObject>

#ifdef Q_OS_WIN
// #include <winbase.h>
#include <windows.h>
#elif Q_OS_MAC
#elif Q_OS_LINUX
#endif

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
