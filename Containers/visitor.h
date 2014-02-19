#ifndef VISITOR_H
#define VISITOR_H

#include <QObject>
#include <QTime>

class Visitor : public QObject
{
    Q_OBJECT
public:
    explicit Visitor(QObject *parent = 0);
    void copyFrom(Visitor *v);

    //Properties
    //new properties should be duplicated to copyFrom(Visitor*) method
    QString BrowserName;
    QString BrowserType;
    QString BrowserVersion;
    QString ChatState;
    QString City_en;
    QString City_ru;
    QString CompanyId;
    QString Country_en;
    QString Country_ru;
    QString CountryCode;
    QString CurrentOperator;
    QString CurrentPageTitle;
    QString CurrentUrl;
    QString CustomName;
    QString Id;
    QString InviteState;
    QString Ip;
    QString Jid;
    QString OperatorDisplayName;
    QString Keywords;
    QString Name;
    QString Organization;
    QString Os;
    QString Referrer;
    QString Relevance;
    QTime TimeOnSite;
    QString Trigger;
    QString ViewedPages;
    QString Visits;

    //Calculated properties
    QString DisplayName(bool appendVisitor=false);
    QString CountryFlag();
    QString vid();
    QString OsIcon();
    QString BrowserIcon();

signals:
    void modified();    

public slots:

private:
    QString _vid;

};

#endif // VISITOR_H
