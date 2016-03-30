@protocol OTTracer;

/**
 * OTSpan establishes the OpenTracing Span contract.
 *
 * See the OpenTracing specification at http://opentracing.io/spec to understand the concepts below.
 */
@protocol OTSpan

/**
 * The Tracer instance that created this span.
 */
- (id<OTTracer>)tracer;

/**
 * Set operation name (if it wasn't set in OTTracer.startSpan or OTTracer.join).
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
 * Add a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 */
- (void)setBaggageItem:(NSString*)key value:(NSString*)value;

/**
 * Retrieve a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 *
 * Returns nil if no baggage item exists for the given key.
 */
- (NSString*)getBaggageItem:(NSString*)key;

/**
 * Mark the finish time and record this span.
 */
- (void) finish;

/**
 * Record this span with the explicitly specified finish time.
 */
- (void) finishWithTime:(NSDate*)finishTime;

@end
