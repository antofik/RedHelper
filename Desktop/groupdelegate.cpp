#include "groupdelegate.h"
#include <QPainter>
#include <QDebug>

GroupDelegate::GroupDelegate(QTreeView *tree, QObject *parent) :
    QStyledItemDelegate(parent)
{
    this->tree = tree;
    grayFont = QColor(60,60,60);
    hyperlink = QColor(79, 141, 196);
    grayBackground = QColor(247,247,247);
}

void GroupDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QRect r = option.rect;
    QFont font = painter->font();
    QPen pen = painter->pen();

    if (!index.parent().isValid())
    {
        painter->setBrush(Qt::red);
        font.setPixelSize(14);
        font.setUnderline(false);
        painter->setFont(font);
        pen.setColor(grayFont);

        //painter->setBackground(Qt::gray);
        painter->fillRect(option.rect, grayBackground);
        if (index.column()==0)
        {
            //if (option.state & QStyle::State_Editing)
            QPixmap icon = tree->isExpanded(index)
                    ? QPixmap(":/Images/Visitors/icon_minus.png")
                    : QPixmap(":/Images/Visitors/icon_plus.png");
                painter->drawPixmap(r.x() + 8, r.y() + 6, 16, 16, icon);

        }        
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(QPoint(r.x() + 32, r.y() + 18), index.data().toString());
    }
    else
    {
        if (option.state & QStyle::State_MouseOver)
        {
            painter->fillRect(option.rect, grayBackground);
        }
        QVariant value = index.data(Qt::DecorationRole);
        int adjust = index.column()==0 ? 24 : 0;
        if (value.isValid() && value.type() == QVariant::Icon)
        {
            QIcon icon = value.value<QIcon>();
            if (icon.availableSizes().count()>0)
            {
                int width = icon.availableSizes().at(0).width();
                icon.paint(painter, r.x()+8 + adjust, r.y(), width, 28);
                adjust += width + 8;
            }
        }

        font.setPixelSize(12);
        if (index.column() == 0 || index.column() == 10)
        {
            font.setUnderline(true);
            pen.setColor(hyperlink);
        }
        else
        {
            font.setUnderline(false);
            pen.setColor(grayFont);
        }
        painter->setPen(pen);
        painter->setFont(font);
        QTextOption textOptions(Qt::AlignLeft);
        textOptions.setWrapMode(QTextOption::NoWrap);
        painter->drawText(r.adjusted(8 + adjust,6,0,0), index.data().toString(), textOptions);
        //painter->drawText(QPoint(r.x() + 32, r.y() + r.height()/2 + font.pixelSize()/2 - 1), index.data().toString(), o);
    }
}

QSize GroupDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (!index.parent().isValid())
        return QSize(-1, 28);
    return QSize(-1, 28);
}
