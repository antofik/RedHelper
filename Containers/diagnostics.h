#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QObject>
#include <QDebug>

#define enter Diagnostics::Log(QString("enter ") + __FUNCTION__);
#define leave Diagnostics::Log(QString("leave ") + __FUNCTION__);
#define _log_(s1) Diagnostics::Log(QString(s1) + __FUNCTION__ + " at " + QString(__FILE__) + ":" + QString::number(__LINE__));
#define _llog_(s1) Diagnostics::Log(QString(s1));

class Diagnostics : public QObject
{
    Q_OBJECT
public:

    static const int LOG_FILE_LIMIT = 10000000; //10MB
    static const int LOG_FILES_COUNT = 10;

    explicit Diagnostics(QObject *parent = 0);
    static Diagnostics *instance();
    static void Log(const QString value);
    void rotateLogs();

signals:

public slots:
    void write(const QString value);

};

#endif // DIAGNOSTICS_H
