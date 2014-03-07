#ifndef SPARKLEAUTOUPDATER_H
#define SPARKLEAUTOUPDATER_H

#include <QString>
#include "autoupdater.h"

class SparkleAutoUpdater : public AutoUpdater {
  public:
    SparkleAutoUpdater(const QString& url);
    ~SparkleAutoUpdater();
    virtual void checkForUpdates();
  private:
    class Private;
    Private* d;
};

#endif // SPARKLEAUTOUPDATER_H
