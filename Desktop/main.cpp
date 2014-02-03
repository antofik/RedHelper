#include "mainwindow.h"
#include <QApplication>
#include "core.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Core::initialize();

    MainWindow w;
    w.show();

    return a.exec();
}
