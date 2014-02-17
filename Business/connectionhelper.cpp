#include "connectionhelper.h"
#include <QDebug>
#include <core.h>
#include <QThread>
#include <QTimer>

ConnectionHelper::ConnectionHelper(QObject *parent) :
    QObject(parent)
{
    static QThread thread;
    moveToThread(&thread);
    connect(Core::network(), SIGNAL(StartWorkers()), SLOT(doWork()));
    thread.start();
}

void ConnectionHelper::doWork()
{
    if (Core::network()->isConnected())
    {
        //Core::network()->updateState();
    }
    QTimer::singleShot(Core::TimeBetweenPresences, this, SLOT(doWork()));
}
