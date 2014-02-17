#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class MenuButton;
}

class MenuButton : public QWidget
{
    Q_OBJECT

public:
    explicit MenuButton(QPixmap icon, QString text, QWidget *parent = 0);
    ~MenuButton();
    void mousePressEvent(QMouseEvent *e);

signals:
    void click();

private:
    Ui::MenuButton *ui;
};

#endif // MENUBUTTON_H
