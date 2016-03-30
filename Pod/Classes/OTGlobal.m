#import "OTGlobal.h"

#import "OTNoop.h"

static NSLock* g_lock;
static id<OTTracer> g_singleton;

@implementation OTGlobal

+ (void)initialize {
    g_lock = [NSLock new];
    g_singleton = [OTNoopTracer new];
}

+ (void)initSharedTracer:(id<OTTracer>)tracer {
    [g_lock lock];
    g_singleton = tracer;
    [g_lock unlock];
}

+ (id<OTTracer>)sharedTracer {
    [g_lock lock];
    id<OTTracer> rval = g_singleton;
    [g_lock unlock];
    return rval;
}

@end
