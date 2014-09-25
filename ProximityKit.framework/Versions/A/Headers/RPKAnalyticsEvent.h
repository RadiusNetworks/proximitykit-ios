//
//  ProximityKit
//
//  Created by Christopher Sexton on 8/15/14.
//  Copyright (c) 2014 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RPKAnalyticsEvent : NSObject

+ (void)postEvent:(NSString *)type withDetails:(NSDictionary *)details;

@end
