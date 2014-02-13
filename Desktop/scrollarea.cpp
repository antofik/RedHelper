#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) :
    QScrollArea(parent)
{
}

QSize ScrollArea::sizeHint() const
{
    return QSize(10, 10);
}
