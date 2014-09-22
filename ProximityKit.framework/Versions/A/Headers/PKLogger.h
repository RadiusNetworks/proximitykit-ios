//
//  PKLogger.h
//  ProximityKit
//
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PKLog(s,...) \
	[PKLogger log:__LEVEL__ format:(s),##__VA_ARGS__]
#define PKLogEmerg(s,...) \
	[PKLogger log:PKLogLevelEmergency format:(s),##__VA_ARGS__]
#define PKLogAlert(s,...) \
	[PKLogger log:PKLogLevelAlert format:(s),##__VA_ARGS__]
#define PKLogCrit(s,...) \
	[PKLogger log:PKLogLevelCritical format:(s),##__VA_ARGS__]
#define PKLogError(s,...) \
	[PKLogger log:PKLogLevelError format:(s),##__VA_ARGS__]
#define PKLogWarn(s,...) \
	[PKLogger log:PKLogLevelWarning format:(s),##__VA_ARGS__]
#define PKLogNotice(s,...) \
	[PKLogger log:PKLogLevelNotice format:(s),##__VA_ARGS__]
#define PKLogInfo(s,...) \
	[PKLogger log:PKLogLevelInformational format:(s),##__VA_ARGS__]
#define PKLogDebug(s,...) \
	[PKLogger log:PKLogLevelDebug format:(s),##__VA_ARGS__]

/** PKLogLevel

The enumerated values for the different log levels. Based on syslog.

*/
typedef NS_ENUM (NSInteger, PKLogLevel)
{
    /** Emergency: System is unusable */
    PKLogLevelEmergency = 0,
    /** Alert: Action must be taken immediately */
    PKLogLevelAlert = 1,
    /** Critical: Critical conditions */
    PKLogLevelCritical = 2,
    /** Error: Error conditions */
    PKLogLevelError = 3,
    /** Warning: Warning conditions */
    PKLogLevelWarning = 4,
    /** Notice: Normal but significant condition */
    PKLogLevelNotice = 5,
    /** Informational: Informational messages */
    PKLogLevelInformational = 6,
    /** Debug: Debug-level messages */
    PKLogLevelDebug = 7
};

/** PKLogger
 *
 * Logging class used internally for Proximity Kit. Can be used to set the
 * logging level and see more informative inforatmion about the internal
 * happenings within the framework.
 *
 * The default log level is set to `PKLogLevelError`
 *
 * This also provides NSLog-like macros for the different levels:
 *
 * - `PKLogEmerg(msg,...)`
 * - `PKLogAlert(msg,...)`
 * - `PKLogCrit(msg,...)`
 * - `PKLogError(msg,...)`
 * - `PKLogWarn(msg,...)`
 * - `PKLogNotice(msg,...)`
 * - `PKLogDebug(msg,...)`
 *
 */
@interface PKLogger : NSObject

/** log:format
 *
 * Print a log message
 *
 * `level` The log level
 *
 * `format` An NSLog-like formatted message
 *
 */
+ (void) log:(PKLogLevel)level format:(NSString *) format, ...;

/** setLevel:
 *
 * Sets the global log level for proximity kit.
 *
 */
+ (void) setLevel:(PKLogLevel)level;

@end
