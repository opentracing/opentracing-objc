#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * OTSpanContext represents Span state that must propagate to descendant Spans
 * and across process boundaries.
 *
 * OTSpanContext is logically divided into two pieces: the user-level "Baggage"
 * (see set_baggage_item and get_baggage_item) that propagates across Span
 * boundaries and any Tracer-implementation-specific fields that are needed to
 * identify or otherwise contextualize the associated Span instance (e.g., a
 * <trace_id, span_id, sampled> tuple).
 *
 * See the OpenTracing specification at http://opentracing.io/spec to understand the concepts below.
 */
@protocol OTSpanContext

/**
 * An iterator for OTSpanContext baggage.
 *
 * If the callback returns false, iteration stops and forEachBaggageItem:
 * returns early.
 */
- (void)forEachBaggageItem:(BOOL (^) (NSString* key, NSString* value))callback;

@end

NS_ASSUME_NONNULL_END
