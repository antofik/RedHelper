#include "operatorhelper.h"
#include "QXmppClient.h"
#include "core.h"

OperatorHelper::OperatorHelper(QObject *parent) :
    QObject(parent)
{
    enter
    _operators = new QVector<Operator*>();
    connect(Core::network(), SIGNAL(operatorsLoaded(QVector<Operator*>*)), SLOT(operatorsLoaded(QVector<Operator*>*)));
    leave
}

QVector<Operator *> *OperatorHelper::items()
{
    return _operators;
}

void OperatorHelper::update()
{
    qDebug() << "operators:update";
    emit Core::network()->loadOperators();
}

void OperatorHelper::operatorsLoaded(QVector<Operator *> *operators)
{
    enter
    _operators = operators;
    qDebug() << "OperatorHelper::operatorsLoaded() " << operators->count();
    emit updated();
    leave
}
