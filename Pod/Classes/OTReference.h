NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const OTReferenceChildOf;
FOUNDATION_EXPORT NSString *const OTReferenceFollowsFrom;

@protocol OTSpanContext;

@interface OTReference : NSObject

@property (strong, nonatomic) NSString* type;
@property (strong, nonatomic) id<OTSpanContext> referencedSpanContext;

/**
 * A convenience helper that constructs an OTReferenceChildOf reference.
 *
 * @see OTReference#initWithType:referencedSpanContext:
 */
+ (OTReference*)childOf:(id<OTSpanContext>)parentContext;

/**
 * A convenience helper that constructs an OTReferenceFollowsFrom reference.
 *
 * @see OTReference#initWithType:referencedSpanContext:
 */
+ (OTReference*)followsFrom:(id<OTSpanContext>)precedingContext;

/**
 * Initialize an OTReference.
 *
 * @param type the identifier for the OTReference type; typically OTReferenceChildOf or OTReferenceFollowsFrom
 * @param referencedSpanContext the OTSpanContext being referred to
 *
 * @see OTReference#childOf
 * @see OTReference#followsFrom
 */
- (instancetype)initWithType:(NSString*)type referencedSpanContext:(id<OTSpanContext>)referencedSpanContext;

@end

NS_ASSUME_NONNULL_END
