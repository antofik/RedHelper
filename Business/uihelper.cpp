#include "uihelper.h"
#include <QDebug>
#include <Qt>
#include <QtCore>

UIHelper::UIHelper(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(update()), SLOT(onUpdate()));
}

void UIHelper::onUpdate()
{
    qApp->processEvents();
}
