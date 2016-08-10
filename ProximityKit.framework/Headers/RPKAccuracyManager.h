//
//  RPKAccuracyManager.h
//  ProximityKit
//
//  Created by Scott Newman on 1/19/16.
//  Copyright © 2016 Radius Networks. All rights reserved.
//

@import UIKit;
#import <Foundation/Foundation.h>

@class RPKBeacon;
@class RPKBeaconRegion;

@protocol RPKAccuracyManagerDelegate <NSObject>
@required
- (void)closestBeaconDidChange:(RPKBeacon *)newClosestBeacon forRegion:(RPKBeaconRegion *)region;
@end

@interface RPKAccuracyManager : NSObject

@property (nonatomic, assign) id<RPKAccuracyManagerDelegate> delegate;
@property (nonatomic, strong) NSNumber *measurementExpirationSeconds;
@property (nonatomic, strong) dispatch_queue_t queue;

- (void)didRangeBeacons:(NSArray *)pkBeacons inRegion:(RPKBeaconRegion *)region;

@end
