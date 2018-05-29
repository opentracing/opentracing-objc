#import <Foundation/Foundation.h>

@protocol OTTracer;

NS_ASSUME_NONNULL_BEGIN

@interface OTGlobal : NSObject

/*
 * Set the shared singleton OTTracer instance. Before this is called for the
 * first time, the OTNoopTracer acts as the shared tracer.
 *
 * @param tracer an OTTracer implementation to replace the existing sharedTracer
 * @see OTGlobal#sharedTracer
 */
+ (void)initSharedTracer:(id<OTTracer>)tracer;

/*
 * Get the shared singleton OTTracer instance.
 *
 * @returns the current shared OTTracer implementation
 * @see OTGlobal#initSharedTracer
 */
+ (id<OTTracer>)sharedTracer;

@end

NS_ASSUME_NONNULL_END
