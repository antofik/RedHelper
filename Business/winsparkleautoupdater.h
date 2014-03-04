#ifndef WINSPARKLEAUTOUPDATER_H
#define WINSPARKLEAUTOUPDATER_H

#include "autoupdater.h"

class WinSparkleAutoUpdater : public AutoUpdater
{
public:
  WinSparkleAutoUpdater(const QString& url);
  ~WinSparkleAutoUpdater();
  virtual void checkForUpdates();
};

#endif // WINSPARKLEAUTOUPDATER_H
