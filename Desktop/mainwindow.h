#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent * event);

private slots:
    void networkStateChanged();
    void loginWindowClosed();
    void diagnostics();

private:
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
