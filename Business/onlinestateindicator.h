#ifndef ONLINESTATEINDICATOR_H
#define ONLINESTATEINDICATOR_H

#include <Qt>
#include <QtCore>
#include <QtGui>
#include <QLabel>

class OnlineStateIndicator : public QLabel
{
    Q_OBJECT
public:
    explicit OnlineStateIndicator(QWidget *parent = 0);

signals:

public slots:

private slots:
    void stateChanged();

};

#endif // ONLINESTATEINDICATOR_H
