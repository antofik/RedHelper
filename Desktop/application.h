#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char **argv);
    bool notify(QObject *, QEvent *);

signals:

public slots:

};

#endif // APPLICATION_H
