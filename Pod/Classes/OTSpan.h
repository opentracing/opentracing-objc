#import <Foundation/Foundation.h>

@protocol OTTracer;

/**
 * XXX
 */
@protocol OTSpan

/**
 * The Tracer instance that created this span.
 */
- (id<OTTracer>)tracer;

/**
 * Set operation name
 */
- (void)setOperationName:(NSString*)operationName;

/**
 * Adds a single tag to the span.
 */
- (void)setTag:(NSString*)key value:(NSString*)value;

/**
 * Log a timestamped event.
 */
- (void)logEvent:(NSString*)eventName;

/**
 * Log a timestamped event along with an arbitrary payload of data.
 */
- (void)logEvent:(NSString*)eventName payload:(NSObject*)payload;

/**
 * Create a log record for given event with a manually specified timestamp
 * and an optional payload.
 */
- (void)log:(NSString*)eventName
  timestamp:(NSDate*)timestamp
    payload:(NSObject*)payload;

/**
 * XXX: docs
 */
- (void)setBaggageItem:(NSString*)key value:(NSString*)value;

/**
 * XXX: docs
 */
- (NSString*)getBaggageItem:(NSString*)key;

/**
 * Mark the end time and record this span.
 */
- (void) finish;

/**
 * Record this span with the explicitly specified finish time.
 */
- (void) finishWithTime:(NSDate*)finishTime;

@end
