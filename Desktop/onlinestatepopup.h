#ifndef ONLINESTATEPOPUP_H
#define ONLINESTATEPOPUP_H

#include <QWidget>

namespace Ui {
class OnlineStatePopup;
}

class OnlineStatePopup : public QWidget
{
    Q_OBJECT

public:
    explicit OnlineStatePopup(QWidget *parent = 0);
    ~OnlineStatePopup();

private:
    Ui::OnlineStatePopup *ui;
};

#endif // ONLINESTATEPOPUP_H
