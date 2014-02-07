#ifndef VISITORUPDATER_H
#define VISITORUPDATER_H

#include <Qt>
#include <QtCore>
#include <QDateTime>
#include <QTime>
#include <QObject>
#include "core.h"
#include "QXmppClient.h"
#include "QXmppElement.h"
#include "visitor.h"

class VisitorUpdater : public QObject
{
    Q_OBJECT

public:
    VisitorUpdater();

public slots:
    void doWork();
    void sendVisitorList();
    void visitorListReceived(QXmppElement *);

signals:
    void NewVisitors(const QStringList &ids, const QVector<Visitor*> *visitors);

private:
    qlonglong _revision;
    QDateTime _lastRequest;
};

#endif // VISITORUPDATER_H
