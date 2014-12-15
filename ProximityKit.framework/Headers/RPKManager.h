//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
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
  RPKManagerNotificationEventDidFailWithError
};

// Notifications.
FOUNDATION_EXPORT NSString *const RPKManagerDidDetermineStateForRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidEnterRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidExitRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidRangeBeaconsInRegionNotification;
FOUNDATION_EXPORT NSString *const RPKManagerDidTriggerAnalyticsEvent;

// Notification user data keys.
FOUNDATION_EXPORT NSString *const RPKManagerNotificationEventKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationRegionKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationRegionStateKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationBeaconsKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationAnalyticsEventDetailsKey;
FOUNDATION_EXPORT NSString *const RPKManagerNotificationAnalyticsEventTypeKey;


/** RPKManager
 *
 * This is the main class for used for interacting with the
 * Proximity Kit SDK.
 *
 * More information can be found at http://proximitykit.com
 */
@interface RPKManager : NSObject <CLLocationManagerDelegate>

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
+ (RPKManager *)managerWithDelegate:(id <RPKManagerDelegate> )delegate;

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
@property (assign) id <RPKManagerDelegate> delegate;

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
@property (assign) id <CLLocationManagerDelegate> locationManagerDelegate;

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
- (void)startRangingIBeacons;

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

@end
