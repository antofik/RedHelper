#include "notificationcenter.h"
#include <NSUserNotification.h>

void Foo::test() {
  NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
  userNotification.title = @"RedHelper";
  userNotification.informativeText = @"Test message";

  [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];
}
