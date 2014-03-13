#include "visitor.h"
#include "diagnostics.h"

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

QString Visitor::DisplayName(bool appendVisitor, bool appendHash)
{
    if (!CustomName.isEmpty()) return CustomName;
    if (appendVisitor) return tr("Visitor #") + Id;
    return appendHash ? "#" + Id : Id;
}

QString Visitor::vid()
{
    if (_vid.isNull() || _vid.isEmpty())
    {
        _vid = Jid.left(Jid.indexOf("@"));
    }
    return _vid;
}

QString Visitor::OsIcon()
{    
    if (Os=="windows") return "xp";
    if (Os=="windows xp") return "xp";
    if (Os=="windows 7") return "win7";
    if (Os=="windows 8") return "win7";
    if (Os=="linux") return "linux";
    if (Os=="mac") return "mac";
    if (Os=="iOS") return "mac";
    if (Os=="ios") return "mac";
    if (Os=="android") return "android";
    return Os;
}

QString Visitor::BrowserIcon()
{
    if (BrowserName.contains("explorer",Qt::CaseInsensitive)) return "ie";
    if (BrowserName.contains("chrome",Qt::CaseInsensitive)) return "chrome";
    if (BrowserName.contains("firefox",Qt::CaseInsensitive)) return "firefox";
    if (BrowserName.contains("safari",Qt::CaseInsensitive)) return "safari";
    if (BrowserName.contains("android",Qt::CaseInsensitive)) return "android";
    if (BrowserName.contains("opera",Qt::CaseInsensitive)) return "opera";
    return BrowserName;
}

void Visitor::redirect(QString login)
{
    isRedirecting = true;
    redirectingTo = login;
}

void Visitor::confirmRedirect(bool ok)
{
    isRedirecting = false;
    CurrentOperator = redirectingTo;
}
