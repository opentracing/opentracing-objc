#import <Foundation/Foundation.h>

@protocol OTTracer;

@interface OTGlobal : NSObject

/*
 * Set the shared singleton OTTracer instance.
 */
+ (void)initSharedTracer:(id<OTTracer>)tracer;

/*
 * Get the shared singleton OTTracer instance.
 */
+ (id<OTTracer>)sharedTracer;

@end
