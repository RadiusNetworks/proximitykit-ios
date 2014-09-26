//
//  ProximityKit
//
//  Copyright (c) 2013 Radius Networks. All rights reserved.
//

#import <Foundation/Foundation.h>

#define RPKLog(s, ...) \
    [RPKLogger log : __LEVEL__ format : (s), ## __VA_ARGS__]
#define RPKLogEmerg(s, ...) \
    [RPKLogger log : RPKLogLevelEmergency format : (s), ## __VA_ARGS__]
#define RPKLogAlert(s, ...) \
    [RPKLogger log : RPKLogLevelAlert format : (s), ## __VA_ARGS__]
#define RPKLogCrit(s, ...) \
    [RPKLogger log : RPKLogLevelCritical format : (s), ## __VA_ARGS__]
#define RPKLogError(s, ...) \
    [RPKLogger log : RPKLogLevelError format : (s), ## __VA_ARGS__]
#define RPKLogWarn(s, ...) \
    [RPKLogger log : RPKLogLevelWarning format : (s), ## __VA_ARGS__]
#define RPKLogNotice(s, ...) \
    [RPKLogger log : RPKLogLevelNotice format : (s), ## __VA_ARGS__]
#define RPKLogInfo(s, ...) \
    [RPKLogger log : RPKLogLevelInformational format : (s), ## __VA_ARGS__]
#define RPKLogDebug(s, ...) \
    [RPKLogger log : RPKLogLevelDebug format : (s), ## __VA_ARGS__]

/** PKLogLevel

   The enumerated values for the different log levels. Based on syslog.

 */
typedef NS_ENUM (NSInteger, RPKLogLevel)
{
    /** Emergency: System is unusable */
    RPKLogLevelEmergency = 0,
    /** Alert: Action must be taken immediately */
    RPKLogLevelAlert = 1,
    /** Critical: Critical conditions */
    RPKLogLevelCritical = 2,
    /** Error: Error conditions */
    RPKLogLevelError = 3,
    /** Warning: Warning conditions */
    RPKLogLevelWarning = 4,
    /** Notice: Normal but significant condition */
    RPKLogLevelNotice = 5,
    /** Informational: Informational messages */
    RPKLogLevelInformational = 6,
    /** Debug: Debug-level messages */
    RPKLogLevelDebug = 7
};

/** RPKLogger
 *
 * Logging class used internally for Proximity Kit. Can be used to set the
 * logging level and see more informative information about the internal
 * happenings within the framework.
 *
 * The default log level is set to `RPKLogLevelError`
 *
 * This also provides NSLog-like macros for the different levels:
 *
 * - `RPKLogEmerg(msg,...)`
 * - `RPKLogAlert(msg,...)`
 * - `RPKLogCrit(msg,...)`
 * - `RPKLogError(msg,...)`
 * - `RPKLogWarn(msg,...)`
 * - `RPKLogNotice(msg,...)`
 * - `RPKLogDebug(msg,...)`
 *
 */
@interface RPKLogger : NSObject

/** log:format
 *
 * Print a log message
 *
 * `level` The log level
 *
 * `format` An NSLog-like formatted message
 *
 */
+ (void)log:(RPKLogLevel)level format:(NSString *)format, ...;

/** setLevel:
 *
 * Sets the global log level for proximity kit.
 *
 */
+ (void)setLevel:(RPKLogLevel)level;

@end
