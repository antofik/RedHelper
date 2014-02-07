#ifndef UIHELPER_H
#define UIHELPER_H

#include <QObject>

class UIHelper : public QObject
{
    Q_OBJECT
public:
    explicit UIHelper(QObject *parent = 0);

signals:
    void openChat(QString id, bool activate);

public slots:

};

#endif // UIHELPER_H
