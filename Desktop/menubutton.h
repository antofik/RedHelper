#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QWidget>
#include <QPixmap>
#include <Qt>

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
    void mouseReleaseEvent(QMouseEvent *e);
    void leaveEvent(QEvent *e);

    static MenuButton * button(QPixmap icon, QString text, const QObject *context, char const* f);

signals:
    void click();

private:
    Ui::MenuButton *ui;
};

#endif // MENUBUTTON_H
