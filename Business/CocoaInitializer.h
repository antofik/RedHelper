#ifndef COCOAINITIALIZER_H
#define COCOAINITIALIZER_H

#import <QString>

class CocoaInitializer
{
  public:
    CocoaInitializer();
    ~CocoaInitializer();
  private:
    class Private;
    Private* d;
};

#endif // COCOAINITIALIZER_H
