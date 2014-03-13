#ifndef OPERATOR_H
#define OPERATOR_H

#include <QObject>
#include <Qt>
#include <QtCore>

class Operator : public QObject
{
    Q_OBJECT
public:
    explicit Operator(QObject *parent = 0);

    QString Login;
    QString Name;
    QString State;
    QString Avatar;
    QString Description;
    bool IsOnDesktop;
    QVector<int> Departments;

signals:

public slots:


};

#endif // OPERATOR_H
