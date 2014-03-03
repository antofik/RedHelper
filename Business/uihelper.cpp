#include "uihelper.h"
#include <QDebug>
#include <Qt>
#include <QtCore>
#include <QApplication>
#include <QWidget>
#include <QSound>
#include "core.h"

#ifdef Q_OS_WIN
#include "Windows.h"
#endif

UIHelper::UIHelper(QObject *parent) :
    QObject(parent)
{
    enter
    connect(this, SIGNAL(update()), SLOT(onUpdate()));
    leave
}

bool UIHelper::isActive()
{
    return false;
    if (qApp->activeWindow()) return true;
    if (qApp->activePopupWidget()) return true;
    if (qApp->activeModalWidget()) return true;
    return false;
}

void UIHelper::playSound()
{
    QSound::play(qApp->applicationDirPath() + "/Incoming.wav");
    flash();
}

void UIHelper::flash()
{
#ifdef Q_OS_WIN
    FLASHWINFO *fInfo = new FLASHWINFO();

    fInfo->cbSize = sizeof(FLASHWINFO);
    fInfo->hwnd = (HWND)Core::ui()->mainWindowHandle;
    fInfo->dwFlags = FLASHW_ALL;
    fInfo->uCount = 4;
    fInfo->dwTimeout = 0;

    FlashWindowEx(fInfo);
#endif

#ifdef Q_OS_MAC
    int i;
#endif
}

void UIHelper::stopFlash()
{
#ifdef Q_OS_WIN
    FLASHWINFO *fInfo = new FLASHWINFO();

    fInfo->cbSize = sizeof(FLASHWINFO);
    fInfo->hwnd = (HWND)Core::ui()->mainWindowHandle;
    fInfo->dwFlags = FLASHW_STOP;

    FlashWindowEx(fInfo);
#endif
#ifdef Q_OS_MAC
    int i;
#endif
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
