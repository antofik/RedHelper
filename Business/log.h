#ifndef LOG_H
#define LOG_H

#include <QObject>
#include "logitem.h"
#include <QVector>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = 0);

    static Log* instance();

    enum Type{
        Info = 0,
        Warning = 1,
        Error = -1,
    };

    static void info(QString message);
    static void warning(QString message);
    static void error(QString message);

    static QVector<LogItem*>* items();

signals:
    void added(LogItem *item);

public slots:

private:
    static void write(LogItem item);
    QVector<LogItem*> _items;
};

#endif // LOG_H
