#ifndef OPERATORHELPER_H
#define OPERATORHELPER_H

#include <QObject>
#include <Qt>
#include <QtCore>
#include "operator.h"

class OperatorHelper : public QObject
{
    Q_OBJECT
public:
    explicit OperatorHelper(QObject *parent = 0);
    QVector<Operator*>* items();

signals:
    void updated();

public slots:
    void update();

private slots:
    void operatorsLoaded(QVector<Operator*>* operators);

private:
    QVector<Operator*>* _operators;

};

#endif // OPERATORHELPER_H
