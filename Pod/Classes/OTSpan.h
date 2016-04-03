@protocol OTTracer;

NS_ASSUME_NONNULL_BEGIN

/**
 * OTSpan establishes the OpenTracing Span contract.
 *
 * See the OpenTracing specification at http://opentracing.io/spec to further understand the concepts below.
 */
@protocol OTSpan

/**
 * @returns the OTTracer implementation that created this span.
 */
- (id<OTTracer>)tracer;

/**
 * Set the Span's operation name (if it wasn't set by the method that yielded the OTSpan in the first place).
 *
 * @param operationName the operation name for this Span
 */
- (void)setOperationName:(NSString*)operationName;

/**
 * Adds a single tag to the span.
 *
 * @param key the key for the tag
 * @param value the tag's value
 */
- (void)setTag:(NSString*)key value:(NSString*)value;

/**
 * Log a timestamped event.
 *
 * @see OTSpan#log:timestamp:payload: for parameter information.
 */
- (void)logEvent:(NSString*)eventName;

/**
 * Log a timestamped event along with an arbitrary payload of data.
 *
 * @see OTSpan#log:timestamp:payload: for parameter information.
 */
- (void)logEvent:(NSString*)eventName payload:(nullable NSObject*)payload;

/**
 * Create a log record for given event with a manually specified timestamp
 * and an optional payload.
 *
 * @param eventName the event name should be the stable identifier for some notable moment in the lifetime of a Span. For instance, a Span representing a browser page load might add an event for each of the Performance.timing moments. While it is not a formal requirement, specific event names should apply to many Span instances: tracing systems can use these event names (and timestamps) to analyze Spans in the aggregate.
 *
 * @param timestamp an explicit timestamp for the log data, or nil to use the current walltime
 *
 * @param payload an optional structured payload object, all or none of which may be recorded by the underlying OTSpan implementation
 */
- (void)log:(NSString*)eventName
  timestamp:(nullable NSDate*)timestamp
    payload:(nullable NSObject*)payload;

/**
 * Add a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 *
 * @param key the key for the Baggage item. Baggage keys have a restricted format: implementations may wish to use them as HTTP header keys (or key suffixes), and of course HTTP headers are case insensitive. As such, Baggage keys MUST match the regular expression (?i:[a-z0-9][-a-z0-9]*), and – per the ?i: – they are case-insensitive. That is, the Baggage key must start with a letter or number, and the remaining characters must be letters, numbers, or hyphens.
 *
 * @param value: the Baggage item value; an opaque string value.
 */
- (void)setBaggageItem:(NSString*)key value:(NSString*)value;

/**
 * Retrieve a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 *
 * @param key the key for the Baggage item.
 *
 * @returns nil if.f. no baggage item exists for the given key.
 */
- (nullable NSString*)getBaggageItem:(NSString*)key;

/**
 * Mark the finish time and record this span.
 */
- (void) finish;

/**
 * Record this span with the explicitly specified finish time.
 *
 * @finishTime an explicit finish timestamp; if finishTime is nil, the local walltime is used instead
 */
- (void) finishWithTime:(nullable NSDate*)finishTime;

@end

NS_ASSUME_NONNULL_END