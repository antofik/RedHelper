#include "cobrowseview.h"
#include "ui_cobrowseview.h"
#include <QWebFrame>
#include "cobrowseobject.h"
#include "core.h"
#include "webpage.h"

const QUrl safe_url("http://web.redhelper.ru/desktop3/index.html");
const QUrl normal_url("http://web.redhelper.ru/desktop3/index.html");
const QUrl debug_url("http://dev/desktop3/index.html");
//const QUrl debug_url("http://test.web.redhelper.ru/desktop3/index.html");

CobrowseView::CobrowseView(QWidget *parent) : QWidget(parent),
    ui(new Ui::CobrowseView)
{
    enter

    _visitor = 0;
    rhDesktop = 0;

    ui->setupUi(this);
    ui->web->setPage(new WebPage());
    ui->web->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->web->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
#ifdef QT_DEBUG
    //ui->web->settings()->enablePersistentStorage("X:/Temp");

    inspector = new QWebInspector();
    inspector->setPage(ui->web->page());
    inspector->setVisible(true);
#endif

    connect(ui->web, SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
    connect(ui->web->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(javaScriptWindowObjectCleared()));

    connect(Core::network(), SIGNAL(mouseReceived(MouseNotification*)), SLOT(mouseReceived(MouseNotification*)));
    connect(Core::network(), SIGNAL(cobrowseReceived(CobrowseNotification*)), SLOT(cobrowseReceived(CobrowseNotification*)));

    this->layout()->invalidate();
    this->layout()->activate();
    leave
}

CobrowseView::~CobrowseView()
{
    enter
    delete ui;
    leave
}

void CobrowseView::setVisitor(Visitor *visitor)
{
    if (_visitor == visitor) return;
    enter
    _visitor = visitor;
    rhDesktop = new CobrowseObject(_visitor);
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhDesktop", rhDesktop);
   // execute("console.log('rhDesktop created at ' + new Date().toISOString())");

#ifdef QT_DEBUG
    ui->web->setUrl(debug_url);
    return;
#endif
    if (!_visitor->CurrentUrl.isNull() && _visitor->CurrentUrl.startsWith("https"))
    {
        ui->web->setUrl(safe_url);
    }
    else
    {
        ui->web->setUrl(normal_url);
    }
    leave
}

void CobrowseView::stop()
{
    if (_visitor == 0) return;
    execute("rhDesktop.stop();");
    _visitor = 0;
}

void CobrowseView::javaScriptWindowObjectCleared()
{
    enter
    if (rhDesktop==0) return;
    ui->web->page()->mainFrame()->addToJavaScriptWindowObject("rhDesktop", rhDesktop);
    leave
}

void CobrowseView::loadFinished(bool ok)
{
    enter
    if (!ok) return;
    if (_visitor==0) return;
    if (rhDesktop==0) return;

    execute("rhDesktop.WTF = 'Qt';");
    execute("rhDesktop.vid = '" + _visitor->vid() + "';");
    execute("rhDesktop.language = 'en';");
    execute("rhDesktop.currentUrl = '" + _visitor->CurrentUrl + "';");
    leave
}

QVariant CobrowseView::execute(QString script)
{
    enter
    if (ui->web->page() && ui->web->page()->mainFrame())
    {
        qDebug() << "SCRIPT: " << script;
        return ui->web->page()->mainFrame()->evaluateJavaScript(script);
    }
    leave
    return "";
}

void CobrowseView::cobrowseReceived(CobrowseNotification* message)
{
    enter
    if (_visitor==0) return;
    QByteArray base64data;
    base64data.append(message->Data.toUtf8());
    execute("rhDesktop.messageReceived('" + base64data.toBase64() + "')");
    leave
}

void CobrowseView::mouseReceived(MouseNotification* message)
{
    enter
    if (_visitor==0) return;
    execute("rhDesktop.moveMouse(" + message->Data + ")");
    leave
}
