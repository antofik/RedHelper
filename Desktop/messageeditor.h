#ifndef MESSAGEEDITOR_H
#define MESSAGEEDITOR_H

#include <QPlainTextEdit>

class MessageEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MessageEditor(QWidget *parent = 0);
    QSize sizeHint() const;
    void keyPressEvent(QKeyEvent *e);


signals:
    void sendMessage();

public slots:

};

#endif // MESSAGEEDITOR_H
