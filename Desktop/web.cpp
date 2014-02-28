#include "web.h"
#include "core.h"

Web::Web(QWidget *parent) :
    QWebView(parent)
{
    enter
    settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings()->setAttribute(QWebSettings::WebAudioEnabled, true);
    settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    leave
}
