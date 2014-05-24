//
//  AMConnect.h
//  Alau.me
//
//  Copyright 2012-2014 Lumen Spark. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AMPromotionManifest;

@interface AMConnect : NSObject 


#pragma mark - Enabling Referral Tracking


/**
 * AMConnect is a singleton class. To enable referral tracking, simply add the following code snippet to your 
 * application:didFinishLaunchingWithOptions: UIApplicationDelegate method:
 *
 * ```
 *   AMConnect *alaume = [AMConnect sharedInstance];
 *
 *   // For debugging purposes only
 *   alaume.isLoggingEnabled = YES;
 *
 *   // Substitute with your own keys; the values below will result in error
 *   [alaume initializeWithAppId:@"px" apiKey:@"8f609af737964c5490025c03462d7318"];
 * ```
 *
 * Alau.me is a powerful tool, which enables a number of distinct scenarios. Most of the properties below are optional
 * and relevant only in specific scenarios e.g. if you offer rewards for user-to-user referrals or app rebates.
 */
+ (AMConnect*) sharedInstance;


/**
 * Returns the public Alau.me app identifier (2-5 characters long).
 */
@property (readonly) NSString *appID;


/**
 * Returns true if this device is already registered. 
 *
 * Note: Once `AMConnect` is initialized, device registration happens automatically.
 */
@property (readonly) BOOL isRegistered;


/**
 * This needs to be called inside AppDelegate's `application:didFinishLaunchingWithOptions:`
 *
 * Note: This method raises `NSInvalidArgumentException` if either appId or apiKey is nil or empty.
 *
 * @param appId corresponding to your app
 * @param apiKey corresponding to your app
 */
- (void)initializeWithAppId:(NSString*)appId apiKey:(NSString*)apiKey;


#pragma mark - Managing Promotion Campaign


/**
 * Returns the Alau.me link used for sharing (referring other users). 
 *
 * Note: Initially this property is nil until your device is registered, which happens automatically.
 */
@property (readonly) NSString *referralLink;


/**
 * Returns the number of successful referals for this user.
 */
@property (readonly) int referralCount;


/**
 * Returns true if the promotion is active and can accept new promoters. Use this property to determine
 * if you should invite the user to participate in the referral program. This property is refreshed 
 * automatically at most once a day.
 */
@property (readonly) BOOL acceptsNewPromoters;


/**
 * A Boolean value that determines if the user has already seen your program invitation.
 *
 * Once you invite the user to participate in the referral program, set this property to YES to make sure 
 * you don't display the same invitation more than once (assuming you use invitations).
 */
@property (readwrite) BOOL didShowPromotionBanner;


/**
 * Returns the currency code (based on the ISO 4217 standard) used in the promotion. Default is USD.
 */
@property (readonly) NSString *currencyCode;


/**
 * Returns the amount the user earns for each successful referral. Use the management console to change it.
 *
 * This will always be 0 if you are rewarding users with virtual goods e.g. in-app perks.
 */
@property (readonly) double cashPerReferral;


/**
 * Returns the number of points the user earns for each successful referral. Use the management console to change it.
 */
@property (readonly) double pointsPerReferral;


/**
 * Returns the minimum number of points required to redeem the rewards. Use the management console to change it.
 */
@property (readonly) double pointsRequiredToRedeem;


/**
 * Returns promotion end date (UTC time). Use the management console to change it.
 */
@property (readonly) NSDate *endDate;


/**
 * Set this property to YES for apps that are free to download.
 */
@property (assign) BOOL isFreeSKU;


/**
 * Returns the number of times the app was brought to the foreground. This property is incremented automatically
 * and is provided purely for your convenience. Use it however you want in your referral program.
 */
@property (readonly) int launchCount;


/**
 * Returns true if the promoter explicitly withdrew from participation in the program. In order to withdraw the user
 * from participation, you must have explicitly called `beginPromoterCancellationWithDelegate:didFinishSelector:`
 */
@property (readonly) BOOL participantWithdrew;


/**
 * Returns the remaining campaign balance (in currency specified by the `currencyCode` property).
 */
@property (readonly) double remainingBalance;


/**
 * Returns the promotion manifest containing various settings used to customize the user experience.
 *
 * What is the manifest file? 
 *
 * The manifest file is a JSON file with various campaign-specific properties. You can define your own 
 * key/value pairs specific to your referral program. The manifest is stored on your server and is 
 * automatically refreshed once a day, if you provide the `promotionManifestURL`.
 */
@property (readonly) AMPromotionManifest* promotionManifest;


/**
 * The URL of the manifest.json file (the manifest file is refreshed automatically at most once a day). 
 */
@property (readwrite, retain) NSURL* promotionManifestURL;


/**
 * Set this property to YES to use the default manifest file (instead of the one loaded from the server).
 *
 * Note: The default manifest should be named: "AMManifest.json" and stored in the main bundle. 
 * Use it for debugging / prototyping so that you don't have to wait a day for the manifest to get refreshed.
 */
@property (assign) BOOL useDefaultPromotionManifest;


/**
 * Withdraws the promoter from participation in the referral program.
 *
 * Note: This method raises `NSInternalInconsistencyException` if `AMConnect` hasn't been initialized yet.
 *
 * @param delegate to call once operation completes with or without an error
 * @param selector with the following signature: `(void)didFinishWithError:(NSError*)error`
 */
- (void)beginPromoterCancellationWithDelegate:(id)delegate didFinishSelector:(SEL)didFinishSelector;


#pragma mark - Getting Referral Information and Redeeming Rewards


/**
 * Returns true if this user was referred by another user.
 *
 * Note: This property is set automatically once the device is successfully registered.
 */
@property (readonly) BOOL wasReferred;


/**
 * Get or set the promo code of the referring user (or nil if this install wasn't referred by anyone). For example, 
 * if a user was referred by opening http://alau.me/df3dg3, this property will return "df3dg3".
 *
 * Note: Since referral tracking is primarily IP-based, this property is set automatically once the device is 
 * successfully registered. However, you can set it manually to indicate that this user was referred by someone. 
 * Once set, it propagates automatically to the Alau.me service. If the install is already referred by someone i.e.
 * the `wasReferred` property returns YES, setting `referredBy` property has no effect.
 */
@property (readwrite, retain) NSString* referredBy;


/**
 * Returns the number of points earned by this user.
 */
@property (readonly) double rewardPoints;


/**
 * A Boolean value that determines if the user has referred more users since the last daily status check.
 *
 * Once you notify the user that they have referred more users, set this property to NO.
 */
@property (readwrite) BOOL hasReferredMoreUsersSinceLastStatusCheck;


/**
 * Updates all reward-related properties.
 *
 * Note: This method raises `NSInternalInconsistencyException` if `initializeWithAppId:apiKey:` method hasn't been called.
 *
 * @param delegate to call once the operation completes with or without an error
 * @param selector with the following signature: `(void)didFinishWithError:(NSError*)error`
 */
- (void)beginRewardStatusCheckWithDelegate:(id)delegate didFinishSelector:(SEL)didFinishSelector;


/**
 * Redeems user's reward points. Use this method only if you are offering monetary rewards or rebates. If you are 
 * offering in-app rewards, use the `rewardPoints` property instead to automatically unlock in-app content once the user
 * earns the required minimum number of points.
 *
 * Note: This method raises `NSInternalInconsistencyException` if `initializeWithAppId:apiKey:` method hasn't been called.
 *
 * @param email address
 * @param delegate to call once the operation completes with or without an error
 * @param selector with the following signature: `(void)didFinishWithError:(NSError*)error`
 */
- (void)beginRewardRedemptionWithEmail:(NSString*)email delegate:(id)delegate didFinishSelector:(SEL)didFinishSelector;


#pragma mark - Troubleshooting & Debugging

/**
 * Set this property to YES to enable Alau.me Connect logging to stderr. For debugging only.
 */
@property (assign) BOOL isLoggingEnabled;


/**
 * Resets all the properties for testing purposes.
 */
- (void)reset;


@end


#pragma mark - Manifest JSON File Wrapper (used only in Advanced scenarios)


/**
 * Class containing promotion manifest i.e. a set of properties used to describe the promotion campaign.
 */
@interface AMPromotionManifest : NSObject 
{
}


/**
 * Returns the value associated with the specified custom key.
 */
- (id)valueForKey:(NSString*)key;


/**
 * Initializes the receiver with the specified property dictionary and defaults.
 */
- (id)initWithDictionary:(NSDictionary*)dictionary defaults:(NSDictionary*)defaults;

@end
