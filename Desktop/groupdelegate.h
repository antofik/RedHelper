#ifndef GROUPDELEGATE_H
#define GROUPDELEGATE_H

#include <QStyledItemDelegate>
#include <QTreeView>

class GroupDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GroupDelegate(QTreeView *tree, QObject *parent = 0);

     void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
     QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:

public slots:

private:
     QTreeView *tree;
     QColor grayFont;
     QColor grayBackground;
     QColor hyperlink;

};

#endif // GROUPDELEGATE_H
