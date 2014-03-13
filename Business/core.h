#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread>
#include "network.h"
#include "visitorupdater.h"
#include "visitorhelper.h"
#include "uihelper.h"
#include "connectionhelper.h"
#include "diagnostics.h"
#include "operatorhelper.h"
#include "log.h"

class VisitorUpdater;
class VisitorHelper;

class Core : public QObject
{
    Q_OBJECT
public:
    //Run-time constants and parameters
    const static qint64 TimeBetweenVisitorlistDiffs = 3000;
    const static qint64 TimeBetweenPresences = 3000000;

    //Initializatin
    explicit Core(QObject *parent = 0);
    static void initialize();

    //Facade
    static Network* network();
    static VisitorUpdater *visitorUpdater();
    static VisitorHelper *visitors();
    static ConnectionHelper *reconnector();
    static UIHelper* ui();
    static OperatorHelper* operators();

private:

};

#endif // CORE_H
