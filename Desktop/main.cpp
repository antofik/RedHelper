#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "core.h"
#include "application.h"
#include <QSound>
#include <iostream>
#include "autoupdater.h"

#ifdef Q_OS_MAC
#include "SparkleAutoUpdater.h"
#include "CocoaInitializer.h"
#endif
#ifdef Q_OS_WIN
#include "winsparkleautoupdater.h"
#endif

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

        AutoUpdater* updater = 0;
        //undone QString updaterUrl = "http://update.redhelper.ru/qt.xml?channel=alpha";
        QString updaterUrl = "http://mfst.pro/update.xml";
#ifdef Q_OS_MAC
        CocoaInitializer cocoaInitializer;
        updater = new SparkleAutoUpdater(updaterUrl);
#endif
#ifdef Q_OS_WIN
        updater = new WinSparkleAutoUpdater(updaterUrl);
#endif
        Core::initialize();
        MainWindow w(updater);

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
