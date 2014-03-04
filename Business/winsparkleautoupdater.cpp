#include <QString>
#include "winsparkleautoupdater.h"
#include "../ThirdParty/winsparkle/winsparkle.h"

WinSparkleAutoUpdater::WinSparkleAutoUpdater(const QString& url)
{
    win_sparkle_set_appcast_url(url.data());
    win_sparkle_init();
}

WinSparkleAutoUpdater::~WinSparkleAutoUpdater()
{
    win_sparkle_cleanup();
}

void WinSparkleAutoUpdater::checkForUpdates()
{
    win_sparkle_check_update_with_ui();
}

