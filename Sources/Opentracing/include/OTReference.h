#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const OTReferenceChildOf;
FOUNDATION_EXPORT NSString *const OTReferenceFollowsFrom;

@protocol OTSpanContext;

/**
 * A Reference pairs a reference type with a SpanContext referee. References
 * are used when starting spans.
 *
 * @see OTTracer#startSpan:references:tags:startTime:
 */
@interface OTReference : NSObject

@property (strong, nonatomic) NSString* type;
@property (strong, nonatomic) id<OTSpanContext> referencedContext;

/**
 * A convenience helper that constructs an OTReferenceChildOf reference.
 *
 * @see OTReference#initWithType:referencedContext:
 */
+ (OTReference*)childOf:(id<OTSpanContext>)parentContext;

/**
 * A convenience helper that constructs an OTReferenceFollowsFrom reference.
 *
 * @see OTReference#initWithType:referencedContext:
 */
+ (OTReference*)followsFrom:(id<OTSpanContext>)precedingContext;

/**
 * Initialize an OTReference.
 *
 * @param type the identifier for the OTReference type; typically
          OTReferenceChildOf or OTReferenceFollowsFrom
 * @param referencedContext the OTSpanContext being referred to
 *
 * @see OTReference#childOf
 * @see OTReference#followsFrom
 */
- (instancetype)initWithType:(NSString*)type referencedContext:(id<OTSpanContext>)referencedContext;

@end

NS_ASSUME_NONNULL_END
