#include "core.h"
#include <Qt>
#include <QDebug>

Core::Core(QObject *parent) :
    QObject(parent)
{
}

void Core::initialize()
{
    qDebug() << "initializing";
}

Network* Core::network()
{
    static Network instance;
    return &instance;
}
