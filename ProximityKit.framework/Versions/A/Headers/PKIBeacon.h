//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PKRegion.h"

/*!
 * @interface PKIBeacon
 */
@interface PKIBeacon : PKRegion

@property (readonly) NSUUID *uuid;
@property (readonly) NSInteger major;
@property (readonly) NSInteger minor;
@property (readonly) NSInteger rssi;
@property (readonly) CLLocationAccuracy accuracy;
@property (readonly) CLProximity proximity;
@property (readonly) CLBeacon *beacon;

- (id)initWith:(NSDictionary *)dict;
- (id)initWithBeacon:(CLBeacon *)beacon dict:(NSDictionary *)dict;
@end