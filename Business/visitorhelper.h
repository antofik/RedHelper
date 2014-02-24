#ifndef VISITORHELPER_H
#define VISITORHELPER_H

#include <Qt>
#include <QtCore>
#include <QObject>
#include "core.h"
#include "visitor.h"

class VisitorHelper : public QObject
{
    Q_OBJECT
public:
    explicit VisitorHelper(QObject *parent = 0);

    Visitor* visitorById(const QString id);
    int onlineCount();

signals:
    void VisitorChanged(const QVector<Visitor*> *added, const QStringList &modified, const QStringList &deleted);

public slots:

private slots:
    void NewVisitorsFromUpdater(const QStringList &ids, const QVector<Visitor*> *visitors);

private:
    QMap<QString, Visitor*> _visitors;

};

#endif // VISITORHELPER_H
