//
//  PKLocationManagerDelegate.h
//  ProximityKit
//
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM (NSInteger, PKRegionType) {
    PKCircleType,
    PKIBeaconType,
};

typedef NS_ENUM (NSInteger, PKRegionState) {
    PKRegionStateUnknown,
    PKRegionStateInside,
    PKRegionStateOutside
};

@class PKManager;
@class PKRegion;

/*!
 @protocol PKManagerDelegate
 @discussion
   The base delegate for Proximity Kit callbacks.

   This includes both callbacks that return the PK custom classes and
   will proxy all the raw CoreLocation callbacks.
*/
@protocol PKManagerDelegate <NSObject>
@required
@optional

/*!
 @method proximityKitDidSync

 @discussion
   Invoked when kit has synced with the server and data is loaded and avaliable.

*/
- (void)proximityKitDidSync:(PKManager *)manager;

/*!
 @method proximityKit:didEnter:

 @discussion
   Invoked when new entering new region. Regions can be Geofences or iBeacons.

*/
- (void)proximityKit:(PKManager *)manager
            didEnter:(PKRegion *)region;

/*!
 @method proximityKit:didExit:

 @discussion
   Invoked when new leaving a region. Regions can be Geofences or iBeacons.

 @param manager
   Instance of the PKManager
 @param region
   The region exited

*/
- (void)proximityKit:(PKManager *)manager
             didExit:(PKRegion *)region;

/*!
 @method proximityKit:didDetermineState:forRegion:

 @discussion
   Invoked when new changing state for a region.

*/
- (void) proximityKit:(PKManager *)manager
    didDetermineState:(PKRegionState)state
            forRegion:(PKRegion *)region;

/*!
 @method proximityKit:didRangeBeacons:inRegion

 @discussion
   Invoked when a new set of beacons are available in the specified region.

   Beacons is an array of PKIBeacon objects.

   If beacons is empty, it may be assumed no beacons that match the specified region are nearby.
   Similarly if a specific beacon no longer appears in beacons, it may be assumed the beacon is no longer received
   by the device.

*/
- (void)proximityKit:(PKManager *)manager
     didRangeBeacons:(NSArray *)beacons
            inRegion:(PKRegion *)region;

/*!
 @method proximityKit:didFailWithError:

 @discussion
   Invoked when an error has occurred.
*/
- (void)proximityKit:(PKManager *)manager
    didFailWithError:(NSError *)error;
@end
