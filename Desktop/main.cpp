#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "core.h"

int main(int argc, char *argv[])
{
    enter
    qDebug() << __VERSION__ << __VERSION3__;

    qApp->addLibraryPath("./plugins");

    QApplication a(argc, argv);
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

    leave

    return a.exec();
}
