#ifndef COCOAINITIALIZER_H
#define COCOAINITIALIZER_H

class CocoaInitializer
{
  public:
    CocoaInitializer(const QString& url);
    ~CocoaInitializer();
  private:
    class Private;
    Private* d;
};

#endif // COCOAINITIALIZER_H
