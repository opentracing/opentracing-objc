#import <Foundation/Foundation.h>

/**
 * SpanContext represents Span state that must propagate to descendant Spans and across process boundaries.
 *
 * SpanContext is logically divided into two pieces: the user-level "Baggage" (see set_baggage_item and get_baggage_item) that propagates across Span boundaries and any Tracer-implementation-specific fields that are needed to identify or otherwise contextualize the associated Span instance (e.g., a <trace_id, span_id, sampled> tuple).
 *
 * See the OpenTracing specification at http://opentracing.io/spec to understand the concepts below.
 */
@protocol OTSpanContext

/**
 * Add a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 *
 * @param key the key for the Baggage item
 * @param value: the Baggage item value; an opaque string value
 */
- (void)setBaggageItem:(NSString*)key value:(NSString*)value;

/**
 * Retrieve a baggage item that propagates along with the distributed trace. See http://opentracing.io/spec/#baggage .
 *
 * @param key the key for the Baggage item.
 * @returns nil if.f. no baggage item exists for the given key.
 */
- (NSString*)getBaggageItem:(NSString*)key;

@end
