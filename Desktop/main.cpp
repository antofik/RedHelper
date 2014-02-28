#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "core.h"
#include "application.h"
#include <QSound>

int main(int argc, char *argv[])
{
    try
    {
        qApp->addLibraryPath("./plugins");

        Application a(argc, argv);
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
