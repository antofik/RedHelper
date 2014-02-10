#include "web.h"

Web::Web(QWidget *parent) :
    QWebView(parent)
{
    settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
}
