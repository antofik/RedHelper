#include "visitor.h"

Visitor::Visitor(QObject *parent) :
    QObject(parent)
{
}

void Visitor::copyFrom(Visitor *v)
{
    BrowserName = v->BrowserName;
    BrowserType = v->BrowserType;
    BrowserVersion = v->BrowserVersion;
    ChatState = v->ChatState;
    City_en = v->City_en;
    City_ru = v->City_ru;
    CompanyId = v->CompanyId;
    Country_en = v->Country_en;
    Country_ru = v->Country_ru;
    CountryCode = v->CountryCode;
    CurrentOperator = v->CurrentOperator;
    CurrentPageTitle = v->CurrentPageTitle;
    CurrentUrl = v->CurrentUrl;
    CustomName = v->CustomName;
    Id = v->Id;
    InviteState = v->InviteState;
    Ip = v->Ip;
    Jid = v->Jid;
    OperatorDisplayName = v->OperatorDisplayName;
    Keywords = v->Keywords;
    Name = v->Name;
    Organization = v->Organization;
    Os = v->Os;
    Referrer = v->Referrer;
    Relevance = v->Relevance;
    TimeOnSite = v->TimeOnSite;
    Trigger = v->Trigger;
    ViewedPages = v->ViewedPages;
    Visits = v->Visits;

    emit modified();
}

QString Visitor::DisplayName()
{
    //if (!CustomName.isEmpty()) return CustomName;
    return "Visitor #" + Id;
}

QString Visitor::vid()
{
    if (_vid.isNull() || _vid.isEmpty())    {
        _vid = Jid.left(Jid.indexOf("@"));
    }
    return _vid;
}
