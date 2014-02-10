#include "messageeditor.h"

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
    if (e->key()==Qt::Key_Return)
    {
        emit sendMessage();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(e);
    }
}
