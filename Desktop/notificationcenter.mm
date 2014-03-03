#include "notificationcenter.h"
#include <NSUserNotification.h>

NotificationCenter::NotificationCenter()
{
    [[NSUserNotificationCenter defaultUserNotificationCenter] setDelegate:self];
}

NotificationCenter *NotificationCenter::instance()
{
    static NotificationCenter instance;
    return &instance;
}

-(BOOL)NotificationCenter:(NSUserNotificationCenter *)center
    shouldPresentNotification:(NSUserNotification *)notification
{
    return YES;
}

void NotificationCenter::test() {
  NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
  userNotification.title = @"RedHelper";
  userNotification.informativeText = @"Test message";

  [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];
}
