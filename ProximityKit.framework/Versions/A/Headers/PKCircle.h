//  Copyright (c) 2013 Radius Networks. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLCircularRegion.h>
#import "PKRegion.h"

/*!
 * @interface PKCircle
 * @discussion Contains a circle region defined by GPS coordinates with a
 *             latitude and longitude.
 */
@interface PKCircle : PKRegion

/*!
 * @property latitude
 * @discussion The latitude value for the center GPS coordinates
 */
@property (readonly) float latitude;

/*!
 * @property longitude
 * @discussion The longitude value for the center GPS coordinates
 */
@property (readonly) float longitude;

/*!
 * @property radius
 * @discussion The length of the radius in meters
 */
@property (readonly) float radius;

- (id)initWith:(NSDictionary *)dict;
- (CLRegion *)region;

@end