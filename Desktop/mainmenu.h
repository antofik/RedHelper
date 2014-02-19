#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void settings();
    void bugreport();
    void about();
    void onlinehelp();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
