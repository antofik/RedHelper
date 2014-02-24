#include "uihelper.h"
#include <QDebug>
#include <Qt>
#include <QtCore>
#include "core.h"

UIHelper::UIHelper(QObject *parent) :
    QObject(parent)
{
    enter
    connect(this, SIGNAL(update()), SLOT(onUpdate()));
    leave
}

void UIHelper::onUpdate()
{
    enter
    qApp->processEvents();
    leave
}

void UIHelper::exit()
{
    enter
    qApp->exit();
    leave
}
