#import <Foundation/Foundation.h>

@protocol OTSpan;
@protocol OTSpanContext;

NS_ASSUME_NONNULL_BEGIN

/**
 * The TextMap format identifier for OTTracer#inject:format:carrier: and
 * OTTracer#extractWithFormat:carrier:
 *
 * The carrier for OTFormatTextMap must be an NSMutableDictionary* instance for
 * `inject` and an NSDictionary* instance for `extract`.
 *
 * @see http://opentracing.io/propagation/
 */
FOUNDATION_EXPORT NSString *const OTFormatTextMap;

/**
 * The HTTP header format identifier for OTTracer#inject:format:carrier: and
 * OTTracer#extractWithFormat:carrier:
 *
 * The carrier for OTFormatHTTPHeaders must be an NSMutableDictionary* instance
 * for `inject` and an NSDictionary* instance for `extract`.
 *
 * Keys and values in these dictionaries must be usable as-is in the respective
 * HTTP headers context.
 *
 * @see http://opentracing.io/propagation/
 */
FOUNDATION_EXPORT NSString *const OTFormatHTTPHeaders;

/**
 * The Binary format identifier for OTTracer#inject:format:carrier: and
 * OTTracer#extractWithFormat:carrier:
 *
 * The carrier for OTFormatBinary must be an NSMutableData* instance for
 * `inject` and an NSData* instance for `extract`.
 *
 * @see http://opentracing.io/propagation/
 */
FOUNDATION_EXPORT NSString *const OTFormatBinary;

/**
 * The error domain for all OpenTracing-related NSErrors.
 */
FOUNDATION_EXPORT NSString *const OTErrorDomain;
/**
 * OTUnsupportedFormat should be used by `OTTracer#inject:format:carrier:` and
 * `OTTracer#extractWithFormat:carrier:` implementations that don't support the
 * requested carrier format.
 */
FOUNDATION_EXPORT NSInteger OTUnsupportedFormatCode;
/**
 * OTInvalidCarrierCode should be used by `OTTracer#inject:format:carrier:` and
 * `OTTracer#extractWithFormat:carrier:` implementations that are unable to use
 * the supplied carrier object, usually because of a type mismatch.
 */
FOUNDATION_EXPORT NSInteger OTInvalidCarrierCode;
/**
 * OTSpanContextCorruptedCode should be used by
 * `OTTracer#extractWithFormat:carrier:` implementations that found part of an
 * injected trace but noticed data corruption and thus could not construct the
 * extrectad OTSpanContext instance.
 */
FOUNDATION_EXPORT NSInteger OTSpanContextCorruptedCode;

/**
 * OTTracer is the starting point for all OpenTracing instrumentation. Use it
 * to create OTSpans, inject/extract them between processes, and so on.
 *
 * OTTracer is thread-safe.
 */
@protocol OTTracer

/**
 * Start a new span with the given operation name. Since there is no parent
 * specified, the returned span will be a trace root.
 *
 * @see OTTracer#startSpan:references:tags:startTime: for paramater and return
 *      value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName;

/**
 * Start a new span with the given operation name and tags. Since there is
 * no parent specified, the returned span will be a trace root.
 *
 * @see OTTracer#startSpan:references:tags:startTime: for paramater and return
 *      value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                   tags:(nullable NSDictionary*)tags;

/**
 * Start a new span with the given operation name and parent span.
 *
 * @see OTTracer#startSpan:references:tags:startTime: for paramater and return
 *      value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                childOf:(nullable id<OTSpanContext>)parent;

/**
 * Start a new span with the given operation name, parent span, and tags.
 *
 * @see OTTracer#startSpan:references:tags:startTime: for paramater and return
 *      value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                childOf:(nullable id<OTSpanContext>)parent
                   tags:(nullable NSDictionary*)tags;

/**
 * Start a new span with the given operation name, parent span, tags, and start
 * time.
 *
 * @see OTTracer#startSpan:references:tags:startTime: for paramater and return
 *      value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                childOf:(nullable id<OTSpanContext>)parent
                   tags:(nullable NSDictionary*)tags
              startTime:(nullable NSDate*)startTime;

/**
 * Start a new span with the given operation name and other optional
 * parameters.
 *
 * @param operationName the operation name for the newly-started OTSpan
 * @param references an optional list of OTReference instances to record causal
 *        relationships
 * @param tags a set of tag keys and values per OTSpan#setTag:value:, or nil to
 *        start with an empty tag map
 * @param startTime an explicitly specified start timestamp for the OTSpan, or
 *        nil to use the current walltime
 * @returns a valid OTSpan instance; it is the caller's responsibility to call
 *          OTSpan#finish
 *
 * @see OTReference
 * @see OTSpan#finish
 * @see OTSpan#setTag:value:
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
             references:(nullable NSArray*)references
                   tags:(nullable NSDictionary*)tags
              startTime:(nullable NSDate*)startTime;

/**
 * @see OTTracer#inject:format:carrier:error:
 */
- (BOOL)inject:(id<OTSpanContext>)spanContext format:(NSString*)format carrier:(id)carrier;
/**
 * Transfer the span information into the carrier of the given format.
 *
 * For example:
 *
 *     NSMutableDictionary* httpHeaders = ...
 *     [[OTTracer sharedTracer] inject:span
 *                              format:OTFormatTextMap
 *                             carrier:headers];
 *
 * @see http://opentracing.io/propagation/
 *
 * @param spanContext the OTSpanContext instance to inject
 * @param format the desired inject carrier format; OTFormatTextMap,
 *        OTFormatHTTPHeaders, and OTFormatBinary are both required carriers for any
 *        OTTracer implementation
 * @param carrier an instance of the carrier type expected by the given `format`
 * @param outError an NSError output parameter in which to record problems with
 *        the injection. OpenTracing errors will be in the OTErrorDomain and may
 *        involve OTUnsupportedFormatCode or OTInvalidCarrierCode.
 *
 * @see OTSpan#context
 * @see OTFormatTextMap
 * @see OTFormatHTTPHeaders
 * @see OTFormatBinary
 * @see OTErrorDomain
 * @see OTUsupportedFormatCode
 * @see OTInvalidCarrierCode
 */
- (BOOL)inject:(id<OTSpanContext>)spanContext format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

/**
 * @see OTTracer#extractWithFormat:carrier:error:
 */
- (nullable id<OTSpanContext>)extractWithFormat:(NSString*)format carrier:(id)carrier;
/**
 * Extract a SpanContext previously (and remotely) injected into the carrier of
 * the given format.
 *
 * For example:
 *
 *     NSDictionary *headerMap = req.headers;  // or similar
 *     id<OTSpanContext> ctx = [
 *         [OTTracer sharedTracer] extractWithFormat:OTFormatTextMap
 *                                           carrier:headerMap];
 *     id<OTSpan> span = [
 *         [OTTracer sharedTracer] startSpan:@"methodName"
 *                                   childOf:ctx];  // ctx may be nil
 *
 * @see http://opentracing.io/propagation/
 *
 * @param format the desired extract carrier format; OTFormatTextMap,
 *        OTFormatHTTPHeaders, and OTFormatBinary are both required carriers for any
 *        OTTracer implementation
 * @param carrier an instance of the carrier type expected by the given `format`
 * @param outError an NSError output parameter in which to record problems with
 *        the injection. OpenTracing errors will be in the OTErrorDomain and may
 *        involve OTUnsupportedFormatCode, OTInvalidCarrierCode, or
 *        OTSpanContextCorruptedCode.
 * @returns a newly-created OTSpanContext that belongs to the trace previously
 *        injected into the carrier (presumably in a remote process)
 *
 * @see OTFormatTextMap
 * @see OTFormatHTTPHeaders
 * @see OTFormatBinary
 * @see OTErrorDomain
 * @see OTUsupportedFormatCode
 * @see OTInvalidCarrierCode
 * @see OTSpanContextCorruptedCode
 * @see OTTracer#startSpan:references:tags:startTime:
 */
- (nullable id<OTSpanContext>)extractWithFormat:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

@end

NS_ASSUME_NONNULL_END
