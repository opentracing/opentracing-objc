@protocol OTTracer;

@interface OTGlobal : NSObject

/*
 * Set the shared singleton OTTracer instance. Before this is called
 * for the first time, the OTNoopTracer acts as the shared tracer.
 */
+ (void)initSharedTracer:(id<OTTracer>)tracer;

/*
 * Get the shared singleton OTTracer instance.
 */
+ (id<OTTracer>)sharedTracer;

@end
