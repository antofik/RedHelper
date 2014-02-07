#include "visitorhelper.h"

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
        qDebug() << "deleting visitor";
        _visitors.remove(deleted.at(i));
    }

    //new & modified visitors
    for(int i=0;i<visitors->count();i++)
    {
        Visitor *v = visitors->at(i);
        if (_visitors.contains(v->Id))
        {
            qDebug() << "updating visitor " << v->Id;
            Visitor *old = _visitors[v->Id];
            old->copyFrom(v);
            modified.append(v->Id);
            delete v;
        }
        else
        {
            qDebug() << "adding new visitor " << v->Id;
            added->append(v);
            _visitors[v->Id] = v;
        }
    }

    emit VisitorChanged(added, modified, deleted);
    delete visitors;
}

Visitor* VisitorHelper::visitorById(const QString id)
{
    return _visitors[id];
}
