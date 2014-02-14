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
    explicit TabButton(QString tabId, bool closable, QWidget *parent = 0);
    ~TabButton();
    void mousePressEvent ( QMouseEvent * event );
    void setText(QString text);
    void highlight();

    Q_PROPERTY(bool selected READ isSelected WRITE setSelected)
    bool isSelected();
    void setSelected(bool value);


public slots:
    void select();
    void unselect();
    void closeClicked();

private:
    Ui::TabButton *ui;
    QString _tabId;    
    bool _isSelected=false;
};

#endif // TABBUTTON_H
