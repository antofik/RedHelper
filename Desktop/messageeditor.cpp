#include "messageeditor.h"
#include <QDebug>
#include "core.h"

MessageEditor::MessageEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    enter
    leave
}

QSize MessageEditor::sizeHint() const
{
    enter
    QSize size(-1,40);
    leave
    return size;
}

void MessageEditor::keyPressEvent(QKeyEvent *e)
{
    enter
    if (e->key()==Qt::Key_Return || e->key()==Qt::Key_Enter)
    {
        emit sendMessage();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(e);
    }
    leave
}
