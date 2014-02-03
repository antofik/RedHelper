#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "network.h"


class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);

    static void initialize();

    static Network* network();

signals:

public slots:

private:


};

#endif // CORE_H
