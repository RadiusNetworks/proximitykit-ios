//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import "RPKMap.h"
#import "RPKRegion.h"
#import "RPKBeacon.h"
#import "RPKBeaconRegion.h"

/*!
 * @interface RPKKit
 */
@interface RPKKit : NSObject

@property NSString *url;
@property NSInteger id;
@property NSString *name;
@property NSArray *beaconRegions;
@property RPKMap *map;
@property NSDictionary *json;

- (id)initWith:(NSDictionary *)dict;
- (RPKRegion *)getRegionForIdentifier:(NSString *)identifier;
- (RPKBeacon *)getIBeaconForCLBeacon:(CLBeacon *)clBeacon;
- (RPKBeaconRegion *)getIBeaconRegionForCLBeaconRegion:(CLBeaconRegion *)clBeaconRegion;


- (void)enumerateIBeaconsUsingBlock:(void (^)(RPKBeacon *iBeacon, NSUInteger idx, BOOL *stop))block;



@end
