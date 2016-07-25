#import "OTReference.h"

NSString* const OTReferenceChildOf = @"child_of";
NSString* const OTReferenceFollowsFrom = @"follows_from";

@implementation OTReference

+ (OTReference*)childOf:(id<OTSpanContext>)parentContext {
    return [[OTReference alloc] initWithType:OTReferenceChildOf referencedContext:parentContext];
}

+ (OTReference*)followsFrom:(id<OTSpanContext>)precedingContext {
    return [[OTReference alloc] initWithType:OTReferenceFollowsFrom referencedContext:precedingContext];
}

- (instancetype)initWithType:(NSString*)type referencedContext:(id<OTSpanContext>)referencedContext {
    if (self = [super init]) {
        _type = type;
        _referencedContext = referencedContext;
    }
    return self;
}

@end
