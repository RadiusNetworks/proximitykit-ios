//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PKManagerDelegate.h"
#import "PKRegion.h"

/*
 *  Class PKManager
 *
 *  Discussion:
 *      This is the main class for used for interacting with the Proximity
 *      Kit SDK.
 *
 *  More information can be found at http://proximitykit.com
 *
 */
@interface PKManager : NSObject <CLLocationManagerDelegate>

/*
 *  managerWithDelegate
 *
 *  Discussion:
 *      Creates the manager, assignes the delegate.
 */
+ (PKManager *)managerWithDelegate:(id <PKManagerDelegate>)delegate;

/*
 *  start
 *
 *  Discussion:
 *      Sets up the manager and syncs data with the server.
  *
 */
- (void)start;


/*
 *  delegate
 *
 *  Discussion:
 *      Primary delegate for the PKManager.
 */
@property (assign) id <PKManagerDelegate> delegate;

/*
 *  locationManager
 *
 *  Discussion:
 *      The instance of CLLocation manager that PKManager wraps and maintains.
 *
 */
@property (readonly) CLLocationManager *locationManager;

/*
 *  locationManagerDelegate
 *
 *  Discussion:
 *      Proxy for all of the CLLocationManager delgate methods. All of the
 *      non-deprecated methods from CLLocationManagerDelegate will be called
 *      on this object.
 *
 *      This is useful for accessing the underlying core location functionality
 *      while using the same locationManager instance that Proximity Kit wraps
 *      and maintains.
 *
 */
@property (assign) id <CLLocationManagerDelegate> locationManagerDelegate;

/*
 * getRegionForIdentifier
 *
 *  Discussion:
 *      Lookup the PKRegion for a given identifier.
 *
 *      Returns nil if no region found.
 *
 */
- (PKRegion *)getRegionForIdentifier:(NSString *)identifier;

/*
 * startRangingIBeacons
 *
 *  Discussion:
 *      Start calculating ranges for iBeacons.
 *
 */
- (void)startRangingIBeacons;

/*
 * stopRangingIBeacons
 *
 *  Discussion:
 *      Stop calculating ranges for iBeacons.
 *
 */
- (void)stopRangingIBeacons;

@end
