#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebPage>

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit WebPage(QObject *parent = 0);

    QString userAgentForUrl(const QUrl &url ) const {
            return QString("Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0; Awesomium) like Gecko");
        }

signals:

public slots:

};

#endif // WEBPAGE_H
