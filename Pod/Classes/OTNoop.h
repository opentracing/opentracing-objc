#import <Foundation/Foundation.h>

#import "OTTracer.h"

NS_ASSUME_NONNULL_BEGIN

/*
 * OTNoopTracer is an implementation of OTTracer that has no side-effects.
 */
@interface OTNoopTracer : NSObject<OTTracer>
@end

NS_ASSUME_NONNULL_END
