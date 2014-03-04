#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "core.h"
#include "application.h"
#include <QSound>
#include <iostream>

int main(int argc, char *argv[])
{
    Application a(argc, argv);

    try
    {
#ifdef Q_OS_WIN
        qApp->addLibraryPath("./plugins");
#endif
#ifdef Q_OS_MAC
        qDebug() << qApp->libraryPaths();
        qApp->setLibraryPaths(QStringList(qApp->applicationDirPath() + "/../PlugIns"));
        qWarning() << qApp->libraryPaths();

        //std::cout << qApp->libraryPaths().at(0).toCFString();

        //qApp->setLibraryPaths(QString("./plugins").split(";"));
#endif

        QCoreApplication::setApplicationName("RedHelper Desktop Application");
        QCoreApplication::setOrganizationDomain("http://redhelper.ru");
        QCoreApplication::setOrganizationName("RedHelper");

        Core::initialize();
        MainWindow w;

#if WIN32
#else
        w.setStyleSheet("font-size: 11px;");
        w.show();
#endif

        return a.exec();
    }
    catch(...)
    {
        qDebug() << "exception";
    }
}
