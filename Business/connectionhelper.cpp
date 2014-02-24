#include "connectionhelper.h"
#include <QDebug>
#include <core.h>
#include <QThread>
#include <QTimer>

ConnectionHelper::ConnectionHelper(QObject *parent) :
    QObject(parent)
{
    enter
    static QThread thread;
    moveToThread(&thread);
    connect(Core::network(), SIGNAL(StartWorkers()), SLOT(doWork()));
    thread.start();
    leave
}

void ConnectionHelper::doWork()
{
    enter
    if (Core::network()->isConnected())
    {
        //Core::network()->updateState();
    }
    QTimer::singleShot(Core::TimeBetweenPresences, this, SLOT(doWork()));
    leave
}
