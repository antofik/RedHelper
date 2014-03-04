#ifndef SPARKLEAUTOUPDATER_H
#define SPARKLEAUTOUPDATER_H

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
