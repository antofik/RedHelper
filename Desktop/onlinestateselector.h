#ifndef ONLINESTATESELECTOR_H
#define ONLINESTATESELECTOR_H

#include <QWidget>

namespace Ui {
class OnlineStateSelector;
}

class OnlineStateSelector : public QWidget
{
    Q_OBJECT

public:
    explicit OnlineStateSelector(QWidget *parent = 0);
    ~OnlineStateSelector();

private:
    Ui::OnlineStateSelector *ui;
};

#endif // ONLINESTATESELECTOR_H
