//
//  AppDelegate.m
//  Alau.me-Demo
//
//  Created by Christoph Zelazowski on 5/25/14.
//  Copyright (c) 2014 Lumen Spark. All rights reserved.
//

#import <Alau.me/AMConnect.h>
#import "AppDelegate.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    AMConnect *alaume = [AMConnect sharedInstance];

    // For debugging purposes only
    alaume.isLoggingEnabled = YES;

    // Substitute with your own keys from https://alau.me/manage/campaigns
    [alaume initializeWithAppId:@"zg" apiKey:@"1c0bd310f7a44e99b694c00ab63b85aa"];

    return YES;
}

@end
