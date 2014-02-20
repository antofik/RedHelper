#include "cobrowseview.h"
#include "ui_cobrowseview.h"
#include <QWebFrame>
#include "cobrowseobject.h"
#include "core.h"
#include "webpage.h"

const QUrl safe_url("http://test.web.redhelper.ru/desktop3/index.html");
const QUrl normal_url("http://test.web.redhelper.ru/desktop3/index.html");

CobrowseView::CobrowseView(QWidget *parent) : QWidget(parent),
    ui(new Ui::CobrowseView)
{
    ui->setupUi(this);
    ui->web->setPage(new WebPage());
    ui->web->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->web->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    connect(ui->web, SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
    connect(ui->web->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(javaScriptWindowObjectCleared()));

    connect(Core::network(), SIGNAL(mouseReceived(MouseNotification*)), SLOT(mouseReceived(MouseNotification*)));
    connect(Core::network(), SIGNAL(cobrowseReceived(CobrowseNotification*)), SLOT(cobrowseReceived(CobrowseNotification*)));

    this->layout()->invalidate();
    this->layout()->activate();
}

CobrowseView::~CobrowseView()
{
    delete ui;
}

void CobrowseView::setVisitor(Visitor *visitor)
{
    _visitor = visitor;
    rhDesktop = new CobrowseObject(_visitor);
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhDesktop", rhDesktop);

    if (!_visitor->CurrentUrl.isNull() && _visitor->CurrentUrl.startsWith("https"))
    {
        ui->web->setUrl(safe_url);
    }else{
        ui->web->setUrl(normal_url);
    }
}

void CobrowseView::javaScriptWindowObjectCleared()
{
    if (rhDesktop==0) return;
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhDesktop", rhDesktop);
}

void CobrowseView::loadFinished(bool ok)
{
    if (!ok) return;
    if (_visitor==0) return;
    if (rhDesktop==0) return;

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

void CobrowseView::cobrowseReceived(CobrowseNotification* message)
{
    QByteArray base64data;
    base64data.append(message->Data.toUtf8());
    execute("rhDesktop.messageReceived('" + base64data.toBase64() + "')");
}

void CobrowseView::mouseReceived(MouseNotification* message)
{
    execute("rhDesktop.mouseMoved('" + message->Data + "')");
}
