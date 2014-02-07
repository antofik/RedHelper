#include "cobrowseview.h"
#include "ui_cobrowseview.h"
#include <QWebFrame>
#include "cobrowseobject.h"

const QUrl safe_url("http://test.web.redhelper.ru/desktop3/index.html");
const QUrl normal_url("http://test.web.redhelper.ru/desktop3/index.html");

CobrowseView::CobrowseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CobrowseView)
{
    ui->setupUi(this);
    ui->web->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->web->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    connect(ui->web, SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
}

CobrowseView::~CobrowseView()
{
    delete ui;
}

void CobrowseView::setVisitor(Visitor *visitor)
{
    _visitor = visitor;

    rhDesktop = new CobrowseObject(visitor);

    if (!_visitor->CurrentUrl.isNull() && _visitor->CurrentUrl.startsWith("https"))
    {
        ui->web->setUrl(safe_url);
    }else{
        ui->web->setUrl(normal_url);
    }

}

void CobrowseView::loadFinished(bool ok)
{
    if (!ok) return;

    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhDesktop", rhDesktop);
    execute("rhDesktop.WTF = 'Qt';");
    execute("rhDesktop.vid = '" + _visitor->vid() + "';");
    execute("rhDesktop.language = 'en';");
    execute("rhDesktop.currentUrl = '" + _visitor->CurrentUrl + "';");
}

QVariant CobrowseView::execute(QString script)
{
    if (ui->web->page() && ui->web->page()->mainFrame())
    {
        qDebug() << "SCRIPT: " << script;

        return ui->web->page()->mainFrame()->evaluateJavaScript(script);
    }
    return "";
}

void CobrowseView::cobrowseReceived(QXmppMessage message)
{
    QByteArray base64data;
    base64data.append(message.body());
    //base64data.append(message.body());
    execute("rhDesktop.messageReceived('" + base64data.toBase64() + "')");
}

void CobrowseView::mouseReceived(QXmppMessage message)
{
    execute("rhDesktop.mouseMoved('" + message.body() + "')");
}
