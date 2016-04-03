#import <Foundation/Foundation.h>

@protocol OTSpan;

NS_ASSUME_NONNULL_BEGIN

/**
 * The TextMap format identifier for OTTracer.inject and OTTracer.join.
 *
 * The carrier for OTFormatTextMap must be an NSMutableDictionary* instance for `inject` and an NSDictionary* instance for `join`.
 *
 * TODO: move to @protocols for writing and reading to TextMaps.
 *
 * @see http://opentracing.io/propagation/
 */
FOUNDATION_EXPORT NSString *const OTFormatTextMap;

/**
 * The Binary format identifier for OTTracer.inject and OTTracer.join.
 *
 * The carrier for OTFormatBinary must be an NSMutableData* instance for `inject` and an NSData* instance for `join`.
 *
 * TODO: move to @protocols for writing and reading to the Binary format.
 *
 * @see http://opentracing.io/propagation/
 */
FOUNDATION_EXPORT NSString *const OTFormatBinary;

/**
 * The error domain for all OpenTracing-related NSErrors.
 */
FOUNDATION_EXPORT NSString *const OTErrorDomain;
/**
 * OTUnsupportedFormat should be used by `inject` and `join` implementations that don't support the requested carrier format.
 */
FOUNDATION_EXPORT NSInteger OTUnsupportedFormatCode;
/**
 * OTInvalidCarrierCode should be used by `inject` and `join` implementations that are unable to use the supplied carrier object, usually because of a type mismatch.
 */
FOUNDATION_EXPORT NSInteger OTInvalidCarrierCode;
/**
 * OTUnsupportedFormat should be used by `join` implementations that found part of an injected trace but noticed data corruption and thus could not construct the joined OTSpan instance.
 */
FOUNDATION_EXPORT NSInteger OTTraceCorruptedCode;

/**
 * OTTracer is the starting point for all OpenTracing instrumentation. Use it
 * to create OTSpans, inject/join them between processes, and so on.
 *
 * OTTracer is thread-safe.
 */
@protocol OTTracer

/**
 * Start a new span with the given operation name. Since there is no parent
 * specified, the returned span will be a trace root.
 *
 * @see OTTracer#startSpan:parent:tags:startTime: for paramater and return value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName;

/**
 * Start a new span with the given operation name and tags. Since there is
 * no parent specified, the returned span will be a trace root.
 *
 * @see OTTracer#startSpan:parent:tags:startTime: for paramater and return value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                   tags:(nullable NSDictionary*)tags;

/**
 * Start a new span with the given operation name and parent span.
 *
 * @see OTTracer#startSpan:parent:tags:startTime: for paramater and return value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                 parent:(nullable id<OTSpan>)parentSpan;

/**
 * Start a new span with the given operation name, parent span, and tags.
 *
 * @see OTTracer#startSpan:parent:tags:startTime: for paramater and return value documentation
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
              parent:(nullable id<OTSpan>)parentSpan
                tags:(nullable NSDictionary*)tags;

/**
 * Start a new span with the given operation name and other optional
 * parameters.
 *
 * @param operationName the operation name for the newly-started OTSpan
 * @param parent an optional parent OTSpan to record a causal relationship
 * @param tags a set of tag keys and values per OTSpan#setTag:value:, or nil to start with an empty tag map
 * @param startTime an explicitly specified start timestamp for the OTSpan, or nil to use the current walltime
 * @returns a valid OTSpan instance; it is the caller's responsibility to call OTSpan#finish
 *
 * @see OTSpan#finish
 * @see OTSpan#setTag:value:
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
              parent:(nullable id<OTSpan>)parentSpan
                tags:(nullable NSDictionary*)tags
           startTime:(nullable NSDate*)startTime;

/**
 * @see OTTracer#inject:format:carrier:error:
 */
- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier;
/**
 * Transfer the span information into the carrier of the given format.
 *
 * For example:
 *
 *     NSMutableDictionary* httpHeaders = ...
 *     [[OTTracer sharedTracer] inject:span format:OTFormatTextMap carrier:headers];
 *
 * @see http://opentracing.io/propagation/
 *
 * @param span the OTSpan instance to inject; it must have been created by this OTTracer implementation
 * @param format the desired inject carrier format; OTFormatTextMap and OTFormatBinary are both required carriers for any OTTracer implementation
 * @param carrier an instance of the carrier type expected by the given `format`
 * @param outError an NSError output parameter in which to record problems with the injection. OpenTracing errors will be in the OTErrorDomain and may involve OTUnsupportedFormatCode or OTInvalidCarrierCode.
 *
 * @see OTFormatTextMap
 * @see OTFormatBinary
 * @see OTErrorDomain
 * @see OTUsupportedFormatCode
 * @see OTInvalidCarrierCode
 */
- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

/**
 * @see OTTracer#join:format:carrier:error:
 */
- (nullable id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier;
/**
 * Create a new span joined to the trace (remotely) injected into the carrier of the given format.
 *
 * For example:
 *
 *     NSDictionary *headerMap = req.headers;  // or similar
 *     id<OTSpan> span = [[OTTracer sharedTracer] join:@"methodName" format:OTFormatTextMap carrier:headerMap];
 *     if (span == nil) {
 *         span = [[OTTracer sharedTracer] startSpan:@"methodName"];  // fall back to create a root span
 *     }
 *
 * @see http://opentracing.io/propagation/
 *
 * @param operationName the desired operation name for the returned OTSpan instance; if unavailable, call OTSpan#setOperationName after joining
 * @param format the desired join carrier format; OTFormatTextMap and OTFormatBinary are both required carriers for any OTTracer implementation
 * @param carrier an instance of the carrier type expected by the given `format`
 * @param outError an NSError output parameter in which to record problems with the injection. OpenTracing errors will be in the OTErrorDomain and may involve OTUnsupportedFormatCode, OTInvalidCarrierCode, or OTTraceCorruptedCode.
 * @returns a newly-created OTSpan that belongs to the trace previously injected into the carrier (presumably in a remote process)
 *
 * @see OTFormatTextMap
 * @see OTFormatBinary
 * @see OTErrorDomain
 * @see OTUsupportedFormatCode
 * @see OTInvalidCarrierCode
 * @see OTTracer#startSpan:parent:tags:startTime:
 * @see OTSpan#setOperationName:
 */
- (nullable id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

@end

NS_ASSUME_NONNULL_END