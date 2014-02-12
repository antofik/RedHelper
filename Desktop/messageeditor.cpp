#include "messageeditor.h"
#include <QDebug>

MessageEditor::MessageEditor(QWidget *parent) : QPlainTextEdit(parent)
{
}

QSize MessageEditor::sizeHint() const
{
    QSize size(-1,40);
    return size;
}

void MessageEditor::keyPressEvent(QKeyEvent *e)
{
    qDebug() << e->key();
    if (e->key()==Qt::Key_Return || e->key()==Qt::Key_Enter)
    {
        emit sendMessage();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(e);
    }
}
