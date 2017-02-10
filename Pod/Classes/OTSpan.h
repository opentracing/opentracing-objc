#import <Foundation/Foundation.h>

@protocol OTSpanContext;
@protocol OTTracer;

NS_ASSUME_NONNULL_BEGIN

/**
 * OTSpan establishes the OpenTracing Span contract.
 *
 * See the OpenTracing specification at http://opentracing.io/spec to further
 * understand the concepts below.
 */
@protocol OTSpan

/**
 * @returns the OTSpanContext associated with this Span.
 */
- (id<OTSpanContext>)context;

/**
 * @returns the OTTracer implementation that created this Span.
 */
- (id<OTTracer>)tracer;

/**
 * Set the Span's operation name (if it wasn't set by the method that yielded
 * the OTSpan in the first place).
 *
 * @param operationName the operation name for this Span
 */
- (void)setOperationName:(NSString*)operationName;

/**
 * Adds a single tag to the span.
 *
 * @param key the key for the tag
 * @param value the tag's value of string type
 */
- (void)setTag:(NSString *)key value:(NSString *)value;

/**
 * Adds a single tag to the span.
 *
 * @param key the key for the tag
 * @param value the tag's value of numeric type
 */
- (void)setTag:(NSString *)key numberValue:(NSNumber *)value;

/**
 * Adds a single tag to the span.
 *
 * @param key the key for the tag
 * @param value the tag's value of boolean type
 */
- (void)setTag:(NSString *)key boolValue:(BOOL)value;

/**
 * Log a moment in the lifetime of the OTSpan instance.
 *
 * @see OTSpan#log:timestamp: for parameter information.
 */
- (void)log:(NSDictionary<NSString*, NSObject*>*)fields;

/**
 * Log a moment in the lifetime of the OTSpan instance.
 *
 * @param fields the fields dictionary should contain key:value pairs where the
 *        keys are NSStrings. Traces are expected to handle NSString or NSNumber
 *        values. They may also handle arbtrary NSObjects.
 *
 * @param timestamp an explicit timestamp for the log data, or nil to use the
 *        current walltime
 */
- (void)log:(NSDictionary<NSString*, NSObject*>*)fields timestamp:(nullable NSDate*)timestamp;

/**
 * Deprecated. Equivalent to
 *
 *   [span log:@{@"event": eventName}];
 *
 */
- (void)logEvent:(NSString*)eventName;

/**
 * Deprecated. Equivalent to
 *
 *   [span log:@{@"event": eventName, @"payload": payload}];
 *
 */
- (void)logEvent:(NSString*)eventName payload:(nullable NSObject*)payload;

/**
 * Deprecated. Equivalent to
 *
 *   [span log:@{@"event": eventName, @"payload": payload} timestamp:timestamp];
 *
 */
- (void)log:(NSString*)eventName
  timestamp:(nullable NSDate*)timestamp
    payload:(nullable NSObject*)payload;

/**
 * Add a baggage item that propagates along with the distributed trace. See
 * http://opentracing.io/spec/#baggage .
 *
 * @param key the key for the Baggage item
 * @param value the Baggage item value; an opaque string value
 * @returns this OTSpan, for chaining
 */
- (id<OTSpan>)setBaggageItem:(NSString*)key value:(NSString*)value;

/**
 * Retrieve a baggage item that propagates along with the distributed trace.
 * See http://opentracing.io/spec/#baggage
 *
 * @param key the key for the Baggage item.
 * @returns nil if.f. no baggage item exists for the given key.
 */
- (nullable NSString*)getBaggageItem:(NSString*)key;

/**
 * Mark the finish time and record this Span.
 */
- (void)finish;

/**
 * Record this Span with the explicitly specified finish time.
 *
 * @param finishTime an explicit finish timestamp; if finishTime is nil, the
 *        local walltime is used instead
 */
- (void)finishWithTime:(nullable NSDate*)finishTime;

@end

NS_ASSUME_NONNULL_END
