//
//  PKMap.h
//  Geofence
//
//  Created by Christopher Sexton on 9/10/13.
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PKMap : NSObject {
    NSMutableArray *_overlays;
}

- (NSArray *) overlays;

@end
