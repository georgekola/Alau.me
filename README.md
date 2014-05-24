# Alau.me SDK

[Alau.me](http://alau.me) is an iOS App Referral Tracking API. It allows you to create short referral links to your app on the App Store and track the resulting app installs. 

You can create short links for a specific ad campaign, or create unique links for each of your users and track user-to-user referrals. 

Alau.me tracks **both** how many people opened the link, and how many people went on to download and use the app. It scales to millions of users and is used by 300+ apps (as of May 2014).

## Usage

+ Create a free [Alau.me](http://alau.me) account.

+ Set the Promoted Link property to your app’s iTunes URL or a custom landing page.

+ Add Alau.me.framework to your XCode project (see Installation instructions below).

+ Add `#import <Alaume/AMConnect.h>` statement to your AppDelegate.h file. 

+ Initialize Alau.me in your app delegate's `application:didFinishLaunchingWithOptions:` method:

 ```objective-c
 AMConnect *alaume = [AMConnect sharedInstance];

 // For debugging purposes only
 alaume.isLoggingEnabled = YES;

 // Substitute with your own keys; the values below will result in error
 [alaume initializeWithAppId:@"px" apiKey:@"8f609af737964c5490025c03462d7318"];
 ```

+ Create a test referral link (click Add Custom Referral Link on the [Campaigns](https://alau.me/manage/campaigns) page).

+ Use custom referral links to track downloads e.g. http://alau.me/px5d34Sd.


**Note:**
Each user automatically gets a unique referral link. You can use those to track user-to-user referrals. Custom referral links can be used for specific ad compaigns or for affiliate tracking.

## How To Test It

+ Copy a referral link to your test device and open it (you should get redirected to the App Store)
+ Install and run your app

Assuming your app has never been installed on your test device before, the Total Referral Count will increase by 1 (see the [Campaigns](https://alau.me/manage/campaigns) page). If you are using a custom referral link, you will also see the number of times the link was opened, and the corresponding number of downloads.

If you have run your app on your test device before, Alau.me will not count that install as a referral. In this case, you will need to unregister that test device so that Alau.me treats it as a new device. Here's how:

+ Run your app and print out the value of the `[AMConnect sharedInstance].referralLink` property
+ Use that link to register your device as a Test Device on the [Campaigns](https://alau.me/manage/campaigns) page
+ Click the Unregister button everytime you want to test a referral on that device

**Troubleshooting:** If you don't see any referrals, then either your `AMConnect` instance is not initialized properly with the correct App ID and API Key, or your app was previously run on your test device. Feel free to email us at developer@lumenspark.com if you have any questions.

## Requirements

iOS 7.0 and above.

## Installation

Alau.me is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

    pod "Alau.me"

Alternatively, if you don't use CocoaPods, do the following:

1. Download Alau.me SDK from https://alau.me/home/developers
2. Copy Alaume SDK into a folder in your project
3. Drag Alaume.framework from Finder to the Frameworks group in your Xcode project
4. Add Security.framework to your project

## Frequently Asked Questions

### How does it work?

Alau.me uses IP address matching to track referrals. In order for a referral to be registered, the referral link and the newly installed app must be opened from the same IP address, within an hour of each other. Of course, IP addresses are not unique. In NAT scenarios, many users share the same publicly visible address. However, it is very unlikely that a random user opens a referral link and another user downloads the corresponding app, behind the same IP address, independent of each other and within an hour. This is true even for very popular apps which get 50,000+ downloads per day. As a result, Alau.me is very accurate in practice.

### How is the app identified?

When the application integrated with Alau.me is run for the first time, Alau.me creates a UUID and stores it in the application's keychain. The UUID is used to register this particular instance of the application with Alau.me service. If you were to delete and re-install the app, the same UUID will be used (since data stored in the keychain persists when the app gets deleted), and therefore the app will be counted as an existing install.

## Common Tasks

### Get the user-specific referral link

Alau.me creates a referral link automatically for every device in the system. You can obtain it by calling the `referralLink` property and let the user share it with their friends. If the device is not registered yet, this method returns nil. Your device is registered automatically upon the first launch. If this fails for any reason (e.g. connectivity issues), Alau.me will retry once every time the app is brought to the foreground.

```objective-c
AMConnect *alaume = [AMConnect sharedInstance];
NSString *referralLink = alaume.referralLink;
```

### Determine the number of referred users

The `referralCount` property returns the number of users that were referred by this user's referralLink. Use this property for analytics purposes, or to reward your users. For example, you can unlock a premium feature if the user refers some number of people to download your app.

```objective-c
AMConnect *alaume = [AMConnect sharedInstance];
int referralCount = alaume.referralCount;
```

### Determine if the user was referred by someone

You can use the `wasReferred` property to determine if someone referred the install of your app on a given device. If the device hasn’t been registered yet, this method returns NO. Use the `referredBy` method to determine the referral ID of the referring user.

```objective-c
AMConnect *alaume = [AMConnect sharedInstance];
BOOL wasReferred = alaume.wasReferred;
```

### Determine if the device is registered with Alau.me

As mentioned above, device registration happens automatically when you initialize `AMConnect`. You can verify if your device is registered already with the `isRegistered` property.

```objective-c
AMConnect *alaume = [AMConnect sharedInstance];
BOOL isRegistered = alaume.isRegistered;
```

### Refresh referral properties

The following properties are cached locally and are refreshed automatically from the server at most 
once per day: `referralCount`, `rewardPoints`, `pointsPerReferral`, `cashPerReferral`, `pointsRequiredToRedeem` and `endDate`. You can refresh those properties on demand, for example, every time you display your Referral Program UI by calling `[AMConnect beginRewardStatusCheckWithDelegate:didFinishSelector:]` method.

```objective-c
- (void)refreshReferralProperties
{
    [[AMConnect sharedInstance] beginRewardStatusCheckWithDelegate:self 
        didFinishSelector:@selector(didFinishRewardStatusCheckWithError:)];
}

- (void)didFinishRewardStatusCheckWithError:(NSError*)error
{
    // Update the UI
}
```

## Author

Lumen Spark LLC, Seattle WA, developer@lumenspark.com

## License

Alau.me is available under commercial license. Please see [Terms of Use](https://alau.me/home/terms) and [Pricing](https://alau.me/home/pricing).

