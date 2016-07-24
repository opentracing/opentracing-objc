#import "OTReference.h"

NSString* const OTReferenceChildOf = @"child_of";
NSString* const OTReferenceFollowsFrom = @"follows_from";

@implementation OTReference

+ (OTReference*)childOf:(id<OTSpanContext>)parentContext {
    return [[OTReference alloc] initWithType:OTReferenceChildOf referencedSpanContext:parentContext];
}

+ (OTReference*)followsFrom:(id<OTSpanContext>)precedingContext {
    return [[OTReference alloc] initWithType:OTReferenceFollowsFrom referencedSpanContext:precedingContext];
}

- (instancetype)initWithType:(NSString*)type referencedSpanContext:(id<OTSpanContext>)referencedSpanContext {
    if (self = [super init]) {
        _type = type;
        _referencedSpanContext = referencedSpanContext;
    }
    return self;
}

@end
