//
//  LocationController.h
//  Geofence
//
//  Created by Christopher Sexton on 9/5/13.
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "PKMap.h"


@interface PKLocationController : NSObject <CLLocationManagerDelegate> {
}

@property (nonatomic, retain) CLLocationManager *locationManager;
@property (nonatomic, retain) PKMap *map;

- (void)locationManager:(CLLocationManager *)manager
    didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation;

- (void)locationManager:(CLLocationManager *)manager
       didFailWithError:(NSError *)error;

-(NSString*)getLat;
-(NSString*)getLng;

- (BOOL)setupFence;

@end
