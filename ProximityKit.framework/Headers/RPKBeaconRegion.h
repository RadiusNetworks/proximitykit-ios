//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "RPKRegion.h"

/*!
 * @interface PKIBeaconRegion
 */
@interface RPKBeaconRegion : RPKRegion

@property (readonly) NSUUID *uuid;
@property (readonly) NSNumber *major;
@property (readonly) NSNumber *minor;
@property (readonly) BOOL hasMajor;
@property (readonly) BOOL hasMinor;
@property (readonly) BOOL enableMonitoring;
@property (readonly) BOOL enableRanging;
@property (readonly) BOOL notifyOnEntry;
@property (readonly) BOOL notifyOnExit;
@property (readonly) BOOL notifyEntryStateOnDisplay;

- (id)initWith:(NSDictionary *)dict;
- (id)initWithRegion:(CLBeaconRegion *)region dict:(NSDictionary *)dict;
- (CLBeaconRegion *)region;

@end
