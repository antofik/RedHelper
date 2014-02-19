#include "visitorhelper.h"
#include "log.h"

VisitorHelper::VisitorHelper(QObject *parent) :
    QObject(parent)
{
    connect(Core::visitorUpdater(), SIGNAL(NewVisitors(QStringList,const QVector<Visitor*>*)), SLOT(NewVisitorsFromUpdater(QStringList,const QVector<Visitor*>*)));
}

void VisitorHelper::NewVisitorsFromUpdater(const QStringList &ids, const QVector<Visitor *> *visitors)
{
    QVector<Visitor*> *added = new QVector<Visitor*>();
    QStringList modified;
    QStringList deleted;

    Log::info("VisitorHelper::NewVisitorsFromUpdater(total=" + QString::number(ids.count()) + ", updated=" + QString::number(visitors->count()) + ")");

    QMap<QString, Visitor*>::iterator iter = _visitors.begin();
    while(iter != _visitors.end())
    {
        if (!ids.contains(iter.key()))
        {
            deleted.append(iter.key());
            iter.value()->ChatState = "offline";
        }
        iter++;
    }

    //remove offline visitors
    for (int i=0;i<deleted.count();i++)
    {
        Log::warning("Removing visitor " + deleted.at(i) + " from stored list");
        _visitors.remove(deleted.at(i));
    }

    //new & modified visitors
    for(int i=0;i<visitors->count();i++)
    {
        Visitor *v = visitors->at(i);
        if (_visitors.contains(v->Id))
        {
            Visitor *old = _visitors[v->Id];
            old->copyFrom(v);
            modified.append(v->Id);
            delete v;
        }
        else
        {
            added->append(v);
            _visitors[v->Id] = v;
        }
    }

    emit VisitorChanged(added, modified, deleted);
    delete visitors;
}

Visitor* VisitorHelper::visitorById(const QString id)
{
    if (!_visitors.contains(id))
    {
        qDebug() << "Dynamic visitor created!";
        Visitor *v = new Visitor();
        v->Id = id;
        _visitors[id] = v;
    }
    return _visitors[id];
}
