//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "RPKAccuracyManager.h"
#import "RPKManagerDelegate.h"
#import "RPKRegion.h"
#import "RPKKit.h"
#import "RPKLogger.h"

/** RPKFetchCompletionHandler
 *
 * Same signature as UIKit's performFetchWithCompletionHandler's block
 *
 */
typedef void (^RPKFetchCompletionHandler)(UIBackgroundFetchResult);

/** RPKManagerNotificationEvent
 *
 * Enumeration of different event types that can trigger notification from RPKManager.
 */
typedef NS_ENUM (NSInteger, RPKManagerNotificationEvent) {
  RPKManagerNotificationEventDidSync,
  RPKManagerNotificationEventDidDetermineStateForRegion,
  RPKManagerNotificationEventDidEnterRegion,
  RPKManagerNotificationEventDidExitRegion,
  RPKManagerNotificationEventDidRangeBeaconsInRegion,
  RPKManagerNotificationEventClosestBeaconDidChange,
  RPKManagerNotificationEventDidFailWithError
};

// Notifications.
FOUNDATION_EXPORT NSString *const RPKManagerDidDetermineStateForRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidEnterRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidExitRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidRangeBeaconsInRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerClosestBeaconDidChangeNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidTriggerAnalyticsEvent;
FOUNDATION_EXPORT NSString *const RPKManagerDidSyncEvent;

// Notification user data keys.
FOUNDATION_EXPORT NSString *const RPKManagerNotificationEventKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationRegionKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationRegionStateKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationBeaconsKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationAnalyticsEventDetailsKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationAnalyticsEventTypeKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationKitKey;


/** RPKManager
 *
 * This is the main class for used for interacting with the
 * Proximity Kit SDK.
 *
 * More information can be found at http://proximitykit.com
 */
@interface RPKManager : NSObject <CLLocationManagerDelegate, RPKAccuracyManagerDelegate>

/** getVersion
 *
 * Get the version string for the Proximity Kit Framework
 *
 */
+ (NSString *)getVersion;

/** manager
 *
 * Creates the manager without a delegate.
 *
 */
+ (RPKManager *)manager;

/** managerWithDelegate
 *
 * Creates the manager, assignes the delegate.
 *
 */
+ (RPKManager *)managerWithDelegate:(id <RPKManagerDelegate> )delegate __deprecated_msg("use managerWithDelegate:andConfig instead");

/** managerWithDelegate:andConfig
 *
 * Creates the manager, assignes the delegate, and uses the supplied
 * configuration dictionary instead of loading the configuration from
 * the plist file.
 *
 */
+ (RPKManager *)managerWithDelegate:(id <RPKManagerDelegate> )delegate andConfig:(NSDictionary *)config;

/** managerWithConfig
 *
 * Creates the manager without a delegate and uses the supplied
 * configuration dictionary instead of loading the configuration from
 * the plist file.
 *
 * Configuration Options:
 *
 * <pre>
 * - kit_url: NSString with the PK kit URL
 * - api_token: PK API Token
 * - allow_cellular_data: Allow cellular data usage
 * - monitor_closest_beacon: Provide a callback event when the closest beacon changes
 * - averaging_seconds: Time period (in seconds) to average accuracy measurements over (optional)
 * </pre>
 *
 */
+ (RPKManager *)managerWithConfig:(NSDictionary *)config;

/** logLevel
 * Set the logging level. Follows syslog convention of levels 0-7.
 *
 * See RPKLogger.h for more details
 *
 * Param: `logLevel`
 *
 * Can take an integer value between 0 and 7, to represent the log level.
 *
 * <pre>
 * 0 - Emergency: System is unusable
 * 1 - Alert: Action must be taken immediately
 * 2 - Critical: Critical conditions
 * 3 - Error: Error conditions
 * 4 - Warning: Warning conditions
 * 5 - Notice: Normal but significant condition
 * 6 - Informational: Informational messages
 * 7 - Debug: Debug-level messages
 * </pre>
 */
- (void)logLevel:(NSInteger)level;

/** start
 *
 * Sets up the manager and synchronizes data with the server.
 *
 */
- (void)start;

/** stop
 *
 * Unregister regions and beacons and stop automatic syncing.
 *
 * While the RPKManager is stopped if `sync` is called the api will be called
 * and data downloaded and synced. However, any regions will not be
 * registered with CoreLocation.
 *
 */
- (void)stop;

/** sync
 *
 * Force a sync with the server. This is not normally required.
 *
 */
- (void)sync;

/** syncWithCompletionHandler
 *
 * Same as `-sync`, but accepts a block for the sync callbacks. This is
 * particularly useful for updating the ProximityKit data when the
 * application in in the background.
 *
 * To take advantage of this you need to implement
 * `application:performFetchWithCompletionHandler:` on your in your
 * application delegate. Then Within that method you can simply call
 * `syncWithCompletionHandler` and pass it the compleation block:
 *
 * <pre>
 * - (void) application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
 * {
 *     // ...
 *     [pkManager syncWithCompletionHandler: completionHandler];
 * }
 * </pre>
 *
 * Be sure to set the fetch interval in your didFinishLaunching method:
 *
 * <pre>
 * - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 * {
 *     // ...
 *     [application setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];
 *     return YES;
 * }
 * </pre>
 *
 *
 * Finally make sure you add `UIBackgroundModes` to your info plist with a string set to 'fetch'
 *
 */
- (void)syncWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;

/** delegate
 *
 * Primary delegate for the RPKManager.
 *
 */
@property (weak, nonatomic) id <RPKManagerDelegate> delegate;

/** locationManager
 *
 * The instance of CLLocation manager that RPKManager wraps and maintains.
 *
 */
@property (readonly) CLLocationManager *locationManager;

/** locationManagerDelegate
 *
 * Proxy for all of the CLLocationManager delgate methods. All of the
 * non-deprecated methods from CLLocationManagerDelegate will be called
 * on this object.
 *
 * This is useful for accessing the underlying core location functionality
 * while using the same locationManager instance that Proximity Kit wraps
 * and maintains.
 *
 */
@property (weak, nonatomic) id <CLLocationManagerDelegate> locationManagerDelegate;

/** kit
 *
 * The representation of the Kit as defined in the Proximity Kit service.
 * This contains lists of iBeacons and Geofences.
 *
 */
@property (readonly) RPKKit *kit;

/** getRegionForIdentifier
 *
 * Lookup the RPKRegion for a given identifier.
 *
 * Returns nil if no region found.
 *
 */
- (RPKRegion *)getRegionForIdentifier:(NSString *)identifier;

/** startRangingIBeacons
 *
 * Start calculating ranges for iBeacons.
 *
 */
- (void)startRangingBeacons;

/** stopRangingIBeacons
 *
 * Stop calculating ranges for iBeacons.
 *
 */
- (void)stopRangingIBeacons;

/** setPartnerIdentifier
 *
 * Sets the partner identifer string for analytics.
 *
 * Limited to 255 characters.
 *
 */
- (void)setPartnerIdentifier:(NSString *)identifier;

/** setAirship
 *
 * Sets the shared instance of Urban Airship SDK instance.
 *
 * Param: `airship` the instance of UAirship manager
 *
 * <pre>
 *   [pkManager setAirship: [UAirship shared]];
 * </pre>
 *
 */
- (void)setAirship:(/* UAirship */id)airship __attribute__((deprecated("Implicit Urban Airship is no longer supported. See tech note for new implementation instructions.")));

/** startAdvertisingWithUUID
 *
 * Begins broadcasting as an iBeacon using `uuid`, `major`, and `minor` parameter values.
 * 
 * Important note: It is not possible to broadcast as a beacon in the background. When implementing,
 * you must ensure that the view that is facilitating the broadcasting stays in the foreground.
 * You might also want to ensure that the device does not go to sleep while that screen is visible.
 *
 */
- (void)startAdvertisingWithUUID:(NSUUID *)uuid major:(NSInteger)major minor:(NSInteger)minor;

/** stopAdvertising
 *
 * Stops advertising as an iBeacon
 *
 */
- (void)stopAdvertising;


@end
