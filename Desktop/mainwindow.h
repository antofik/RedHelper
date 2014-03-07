#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include "autoupdater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AutoUpdater* updater, QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent * event);

private slots:
    void networkStateChanged();
    void loginWindowClosed();
    void showLoginWindow();
    void diagnostics();

private:
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
