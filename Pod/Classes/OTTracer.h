#import <Foundation/Foundation.h>

@protocol OTSpan;

/**
 * The TextMap format string for OTTracer.inject and OTTracer.join.
 */
FOUNDATION_EXPORT NSString *const OTFormatTextMap;
FOUNDATION_EXPORT NSString *const OTFormatBinary;

FOUNDATION_EXPORT NSString *const OTErrorDomain;
FOUNDATION_EXPORT NSInteger OTUnsupportedFormatCode;
FOUNDATION_EXPORT NSInteger OTInvalidCarrierCode;
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
 */
- (id<OTSpan>)startSpan:(NSString*)operationName;

/**
 * Start a new span with the given operation name and tags. Since there is
 * no parent specified, the returned span will be a trace root.
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                   tags:(NSDictionary*)tags;

/**
 * Start a new span with the given operation name and parent span.
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
                 parent:(id<OTSpan>)parentSpan;

/**
 * Start a new span with the given operation name, parent span, and tags.
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
              parent:(id<OTSpan>)parentSpan
                tags:(NSDictionary*)tags;

/**
 * Start a new span with the given operation name and other optional
 * parameters.
 */
- (id<OTSpan>)startSpan:(NSString*)operationName
              parent:(id<OTSpan>)parentSpan
                tags:(NSDictionary*)tags
           startTime:(NSDate*)startTime;

/**
 * Transfer the span information into the carrier of the given format.
 *
 * For example:
 *
 *     NSMutableDictionary* httpHeaders = ...
 *     [[OTTracer sharedTracer] inject:span format:OTFormatTextMap carrier:headers];
 *
 * See http://opentracing.io/propagation/
 */
- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier;
- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

/**
 * Create a new span joined to the trace (remotely) injected into the carrier of the given format.
 *
 * See http://opentracing.io/propagation/
 */
- (id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier;
- (id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError;

@end
