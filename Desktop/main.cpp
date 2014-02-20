#include "mainwindow.h"
#include <QApplication>
#include "core.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Core::initialize();

    MainWindow w;
#if WIN32
#else
    w.setStyleSheet("font-size: 11px;");
    w.show();
#endif

    return a.exec();
}
