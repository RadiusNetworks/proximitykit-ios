//
//  ProximityKit
//
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM (NSInteger, RPKRegionType) {
    RPKCircleType,
    RPKIBeaconType,
};

typedef NS_ENUM (NSInteger, RPKRegionState) {
    RPKRegionStateUnknown,
    RPKRegionStateInside,
    RPKRegionStateOutside
};

@class RPKManager;
@class RPKRegion;

/*!
 @protocol RPKManagerDelegate
 @discussion
   The base delegate for Proximity Kit callbacks.

   This includes both callbacks that return the RPK custom classes and
   will proxy all the raw CoreLocation callbacks.
*/
@protocol RPKManagerDelegate <NSObject>
@required
@optional

/*!
 @method proximityKitDidSync

 @discussion
   Invoked when kit has synced with the server and data is loaded and avaliable.

*/
- (void)proximityKitDidSync:(RPKManager *)manager;

/*!
 @method proximityKit:didEnter:

 @discussion
   Invoked when new entering new region. Regions can be Geofences or iBeacons.

*/
- (void)proximityKit:(RPKManager *)manager
            didEnter:(RPKRegion *)region;

/*!
 @method proximityKit:didExit:

 @discussion
   Invoked when new leaving a region. Regions can be Geofences or iBeacons.

 @param manager
   Instance of the RPKManager
 @param region
   The region exited

*/
- (void)proximityKit:(RPKManager *)manager
             didExit:(RPKRegion *)region;

/*!
 @method proximityKit:didDetermineState:forRegion:

 @discussion
   Invoked when new changing state for a region.

*/
- (void) proximityKit:(RPKManager *)manager
    didDetermineState:(RPKRegionState)state
            forRegion:(RPKRegion *)region;

/*!
 @method proximityKit:didRangeBeacons:inRegion

 @discussion
   Invoked when a new set of beacons are available in the specified region.

   Beacons is an array of RPKBeacon objects.

   If beacons is empty, it may be assumed no beacons that match the specified region are nearby.
   Similarly if a specific beacon no longer appears in beacons, it may be assumed the beacon is no longer received
   by the device.

*/
- (void)proximityKit:(RPKManager *)manager
     didRangeBeacons:(NSArray *)beacons
            inRegion:(RPKRegion *)region;

/*!
 @method proximityKit:didFailWithError:

 @discussion
   Invoked when an error has occurred.
*/
- (void)proximityKit:(RPKManager *)manager
    didFailWithError:(NSError *)error;
@end
