//
//  ViewController.m
//  Alau.me-Demo
//
//  Created by Christoph Zelazowski on 5/25/14.
//  Copyright (c) 2014 Lumen Spark. All rights reserved.
//

#import <Alau.me/AMConnect.h>
#import "ViewController.h"

@interface ViewController ()
@property (nonatomic, strong) IBOutlet UITextView *textView;
@end

@implementation ViewController

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (IBAction)updateView:(id)sender
{
    AMConnect *alaume = [AMConnect sharedInstance];

    if (alaume.isRegistered == NO || alaume.referralLink.length == 0)
    {
        self.textView.text =
            @"Your device is being registered with Alau.me. Device registration happens automatically.\n\n"
            @"If it fails for any reason, e.g. network connectivity issues, AMConnect will retry the next time the app is brought to foreground.";
    }
    else
    {
        self.textView.text = [NSString stringWithFormat:
            @"Every device gets a unique referral link, which you can use for user-to-user referrals.\n\n"
            @"Below are the values of a few key AMConnect properties for this device:\n\n---\n"
            @"Referral Link: %@\nReferral Count: %d\nReferred By: %@\nLaunch Count: %d\n---",
            alaume.referralLink, alaume.referralCount, alaume.referredBy.length > 0 ? alaume.referredBy : @"Nobody", alaume.launchCount];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateView:) name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self updateView:nil];
}

@end
