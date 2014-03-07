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
        AutoUpdater* updater = 0;
        QCoreApplication::setApplicationName("RedHelper Desktop Application");
        QCoreApplication::setOrganizationDomain("http://redhelper.ru");
        QCoreApplication::setOrganizationName("RedHelper");
#ifdef Q_OS_WIN
        qApp->addLibraryPath("./plugins");
        //removed updater = new WinSparkleAutoUpdater("http://mfst.pro/update-win.xml");
#endif
#ifdef Q_OS_MAC
        qApp->setLibraryPaths(QStringList(qApp->applicationDirPath() + "/../PlugIns"));
        CocoaInitializer cocoaInitializer;
        updater = new SparkleAutoUpdater("http://mfst.pro/update-mac.xml");
#endif
        Core::initialize();
        MainWindow w(updater);
#ifndef Q_OS_WIN
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
