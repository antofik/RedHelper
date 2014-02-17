#ifndef ONLINESTATESELECTOR_H
#define ONLINESTATESELECTOR_H

#include <QWidget>
#include <QDebug>
#include <QMenu>

namespace Ui {
class OnlineStateSelector;
}

class OnlineStateSelector : public QWidget
{
    Q_OBJECT

public:
    explicit OnlineStateSelector(QWidget *parent = 0);
    ~OnlineStateSelector();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void leaveEvent(QEvent *e);

public slots:

signals:

private slots:
    void changeAccount();
    void exit();
    void stateChanged();
    void menuClosed();

private:
    QMenu *menu;
    Ui::OnlineStateSelector *ui;
};

#endif // ONLINESTATESELECTOR_H
