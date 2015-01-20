//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "RPKRegion.h"

/*!
 * @interface PKIBeacon
 */
@interface RPKBeacon : RPKRegion

@property (readonly) NSUUID *uuid;
@property (readonly) NSNumber *major;
@property (readonly) NSNumber *minor;
@property (readonly) NSNumber *rssi;
@property (readonly) CLLocationAccuracy accuracy;
@property (readonly) CLProximity proximity;
@property (readonly) CLBeacon *beacon;

- (id)initWith:(NSDictionary *)dict;
- (id)initWithBeacon:(CLBeacon *)beacon dict:(NSDictionary *)dict;
@end
