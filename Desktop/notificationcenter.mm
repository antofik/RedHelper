#include "notificationcenter.h"
//#include <NSUserNotification.h>
#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <objc/runtime.h>
#include <Carbon/Carbon.h>

@interface NotificationCenterDelegate : NSObject<NSUserNotificationCenterDelegate>
  -(BOOL)userNotificationCenter:(NSUserNotificationCenter*)center shouldPresentNotification:(NSUserNotification*)notification;
@end

@implementation NotificationCenterDelegate
-(BOOL)userNotificationCenter:(NSUserNotificationCenter*)center shouldPresentNotification:(NSUserNotification*)notification
{
    return YES;
}
@end

NotificationCenter::NotificationCenter()
{
    NotificationCenterDelegate *delegate = [[NotificationCenterDelegate alloc] init];
    [[NSUserNotificationCenter defaultUserNotificationCenter] setDelegate:delegate];
}

NotificationCenter *NotificationCenter::instance()
{
    static NotificationCenter instance;
    return &instance;
}

void NotificationCenter::showNotification(QString title, QString message)
{

  NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
  userNotification.title = [NSString stringWithFormat:@"%@", title.toCFString()];
  userNotification.informativeText = [NSString stringWithFormat:@"%@", message.toCFString()];

  [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];

  [NSApp requestUserAttention: NSInformationalRequest];
}
