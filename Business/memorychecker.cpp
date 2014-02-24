#include "memorychecker.h"
#include <QProcess>

MemoryChecker::MemoryChecker(QObject *parent) :
    QObject(parent)
{
}

int MemoryChecker::GetMemoryUsage()
{
    return -1;
}
