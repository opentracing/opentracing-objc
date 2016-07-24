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
 * @param eventName the event name should be the stable identifier for some
 *        notable moment in the lifetime of a Span. For instance, a Span representing a
 *        browser page load might add an event for each of the Performance.timing
 *        moments. While it is not a formal requirement, specific event names should
 *        apply to many Span instances: tracing systems can use these event names (and
 *        timestamps) to analyze Spans in the aggregate.
 *
 * @param timestamp an explicit timestamp for the log data, or nil to use the
 *        current walltime
 *
 * @param payload an optional structured payload object, all or none of which
 *        may be recorded by the underlying OTSpan implementation
 */
- (void)log:(NSString*)eventName
  timestamp:(nullable NSDate*)timestamp
    payload:(nullable NSObject*)payload;

/**
 * Mark the finish time and record this Span.
 */
- (void) finish;

/**
 * Record this Span with the explicitly specified finish time.
 *
 * @param finishTime an explicit finish timestamp; if finishTime is nil, the
 *        local walltime is used instead
 */
- (void) finishWithTime:(nullable NSDate*)finishTime;

@end

NS_ASSUME_NONNULL_END
