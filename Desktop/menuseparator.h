#ifndef MENUSEPARATOR_H
#define MENUSEPARATOR_H

#include <QWidget>

namespace Ui {
class MenuSeparator;
}

class MenuSeparator : public QWidget
{
    Q_OBJECT

public:
    explicit MenuSeparator(QWidget *parent = 0);
    ~MenuSeparator();

private:
    Ui::MenuSeparator *ui;
};

#endif // MENUSEPARATOR_H
