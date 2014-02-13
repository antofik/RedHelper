#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QWidget>

namespace Ui {
class TabButton;
}

class TabButton : public QWidget
{
    Q_OBJECT

public:
    explicit TabButton(QString tabId, QWidget *parent = 0);
    ~TabButton();
    void mousePressEvent ( QMouseEvent * event );
    void setText(QString text);

    Q_PROPERTY(bool selected READ isSelected WRITE setSelected)
    bool isSelected();
    void setSelected(bool value);


public slots:
    void select();
    void unselect();

private:
    Ui::TabButton *ui;
    QString _tabId;    
    bool _isSelected=false;
};

#endif // TABBUTTON_H
