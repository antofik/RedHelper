#include "visitorupdater.h"
#include <QTimer>
#include "memorychecker.h"

VisitorUpdater::VisitorUpdater() : QObject(0)
{    
    enter
    _lastRequest = QDateTime::currentDateTime();

    static QThread thread;
    moveToThread(&thread);
    connect(Core::network(), SIGNAL(StartWorkers()), SLOT(doWork()));
    connect(Core::network(), SIGNAL(visitorListReceived(QXmppElement *)), SLOT(visitorListReceived(QXmppElement *)));
    thread.start();
    leave
}

void VisitorUpdater::doWork()
{
    enter
    sendVisitorList();
    leave
}

void VisitorUpdater::sendVisitorList()
{
    enter
    QDateTime time = QDateTime::currentDateTime();
    qint64 delta = _lastRequest.msecsTo(time);
    if (delta < Core::TimeBetweenVisitorlistDiffs)
    {
        QTimer::singleShot(Core::TimeBetweenVisitorlistDiffs - delta, this, SLOT(sendVisitorList()));
        return;
    }

    QXmppClient* client = Core::network()->client;
    if (client->isConnected() && client->isAuthenticated())
    {
        try
        {
            _lastRequest = QDateTime::currentDateTime();

            QXmppIq iq;
            QXmppElement query;
            query.setTagName("query");
            query.setAttribute("xmlns", "consultant:visitorlistdiff");
            QXmppElement revision;
            revision.setTagName("revision");
            revision.setValue(QString::number(_revision));
            query.appendChild(revision);
            iq.setExtensions(QXmppElementList() << query);
            client->sendPacket(iq);
        }
        catch (const std::exception& ex)
        {
            qDebug() << "VisitorUpdater Error";
            //qDebug() << "VisitorUpdater Error: " << ex;
        }
        catch (const std::string& ex)
        {
            qDebug() << "VisitorUpdater Error";
            //qDebug() << "VisitorUpdater Error: " << ex;
        }
        catch(...)
        {
            qDebug() << "VisitorUpdater Error";
        }
    }

    QTimer::singleShot(Core::TimeBetweenVisitorlistDiffs, this, SLOT(sendVisitorList()));
    leave
}

void VisitorUpdater::visitorListReceived(QXmppElement *element)
{
    enter
    _lastRequest = QDateTime::currentDateTime();

    QString q = element->value();
    QXmppElement e = element->firstChildElement("revision");
     QString revision = element->firstChildElement("revision").value();
    _revision = revision.toLongLong();
    QStringList ids = element->firstChildElement("ids").value().split(",");

    QVector<Visitor*> *updatedVisitors = new QVector<Visitor*>();
    QXmppElement visitorElement = element->firstChildElement("visitors").firstChildElement("visitor");

    while(!visitorElement.isNull())
    {
        Visitor *visitor = new Visitor();        
        visitor->BrowserName = visitorElement.firstChildElement("browserName").value();
        visitor->BrowserType = visitorElement.firstChildElement("browserType").value();
        visitor->BrowserVersion = visitorElement.firstChildElement("browserVersion").value();
        visitor->ChatState = visitorElement.firstChildElement("chatState").value();
        visitor->City_en = visitorElement.firstChildElement("city_en").value();
        visitor->City_ru = visitorElement.firstChildElement("city_ru").value();
        visitor->CompanyId = visitorElement.firstChildElement("companyId").value();
        visitor->Country_en = visitorElement.firstChildElement("country_en").value();
        visitor->Country_ru = visitorElement.firstChildElement("country_ru").value();
        visitor->CountryCode = visitorElement.firstChildElement("country_code").value();
        visitor->CurrentOperator = visitorElement.firstChildElement("currentOperator").value();
        visitor->CurrentPageTitle = visitorElement.firstChildElement("currentPageTitle").value();
        visitor->CurrentUrl = visitorElement.firstChildElement("currentUrl").value();
        visitor->CustomName = visitorElement.firstChildElement("customName").value();
        visitor->InviteState = visitorElement.firstChildElement("inviteState").value();
        visitor->Ip = visitorElement.firstChildElement("ip").value();
        visitor->Jid = visitorElement.firstChildElement("jid").value();
        visitor->OperatorDisplayName = visitorElement.firstChildElement("operatorDisplayName").value();
        visitor->Organization = visitorElement.firstChildElement("org").value();
        visitor->Os = visitorElement.firstChildElement("os").value().trimmed().toLower();
        visitor->Referrer = visitorElement.firstChildElement("referrer").value();
        QString time = visitorElement.firstChildElement("timeOnSite").value();
        visitor->TimeOnSite = QTime(0,0,0).addSecs(time.toInt());
        if (time.toInt()>60)
        {
            QString t = visitor->TimeOnSite.toString();
            qDebug() << "timeonsite" << t;
        }
        visitor->Trigger = visitorElement.firstChildElement("trigger").value();
        visitor->ViewedPages = visitorElement.firstChildElement("viewedPages").value();
        visitor->Visits = visitorElement.firstChildElement("visits").value();
        visitor->Id = visitor->Jid.left(visitor->Jid.indexOf("@"));

        if (visitor->ChatState=="chat"
                && !visitor->CurrentOperator.isEmpty()
                && visitor->CurrentOperator!=Core::network()->User)
        {
            visitor->ChatState = "busy";
        }

        updatedVisitors->append(visitor);
        visitorElement = visitorElement.nextSiblingElement("visitor");       
    }

    _log_(QString::number(updatedVisitors->count()) + " visitors updated. " + QString::number(ids.count()) + " visitors online")

    emit NewVisitors(ids, updatedVisitors);
    leave
}
