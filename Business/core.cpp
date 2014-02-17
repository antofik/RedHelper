#include "core.h"
#include <Qt>
#include <QDebug>

Core::Core(QObject *parent) : QObject(parent)
{
}

void Core::initialize()
{
    //create instances of helpers
    network();
    visitorUpdater();
    visitors();
    ui();
    reconnector();

    emit Core::network()->StartWorkers();
}

VisitorUpdater* Core::visitorUpdater()
{
    static VisitorUpdater updater;
    return &updater;
}

Network* Core::network()
{
    static Network instance;
    return &instance;
}

VisitorHelper* Core::visitors()
{
    static VisitorHelper instance;
    return &instance;
}

UIHelper* Core::ui()
{
    static UIHelper instance;
    return &instance;
}

ConnectionHelper* Core::reconnector()
{
    static ConnectionHelper instance;
    return &instance;
}
