#include "scrollarea.h"
#include "core.h"

ScrollArea::ScrollArea(QWidget *parent) :
    QScrollArea(parent)
{
    enter
    leave
}

QSize ScrollArea::sizeHint() const
{
    enter
    return QSize(10, 10);
}
