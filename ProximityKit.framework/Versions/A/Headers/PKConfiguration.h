//
//  PKConfiguration.h
//  Geofence
//
//  Created by Christopher Sexton on 9/10/13.
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PKConfiguration : NSObject {
@private
    NSDictionary* config;
}

@property NSString *url;
@property NSString *apiToken;
@property NSString *mapName;


@end
