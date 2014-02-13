#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>

class ScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollArea(QWidget *parent = 0);
    QSize sizeHint() const;

signals:

public slots:

};

#endif // SCROLLAREA_H
