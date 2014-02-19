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
    w.show();
#endif

    return a.exec();
}
