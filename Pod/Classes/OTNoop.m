#import "OTNoop.h"
#import "OTSpan.h"
#import "OTSpanContext.h"

@class OTNoopSpan;
@class OTNoopSpanContext;

// Initialized in OTNoopTracer.initialize:
static OTNoopTracer* g_defaultNoopTracer;
static OTNoopSpan* g_defaultNoopSpan;
static OTNoopSpanContext* g_defaultNoopSpanContext;

@interface OTNoopSpanContext : NSObject<OTSpanContext>
@end

@implementation OTNoopSpanContext
- (void)setBaggageItem:(NSString*)key value:(NSString*)value {}
- (NSString*)getBaggageItem:(NSString*)key { return nil; }
@end

@interface OTNoopSpan : NSObject<OTSpan>
@end

@implementation OTNoopSpan
- (id<OTTracer>)tracer { return g_defaultNoopTracer; }
- (id<OTSpanContext>)context { return g_defaultNoopSpanContext; }
- (void)setOperationName:(NSString*)operationName {}
- (void)setTag:(NSString*)key value:(NSString*)value {}
- (void)logEvent:(NSString*)eventName {}
- (void)logEvent:(NSString*)eventName payload:(NSObject*)payload {}
- (void)log:(NSString*)eventName timestamp:(NSDate*)timestamp payload:(NSObject*)payload {}
- (void)finish {}
- (void)finishWithTime:(NSDate*)finishTime {}
@end

@implementation OTNoopTracer

+ (void)initialize {
    g_defaultNoopSpan = [OTNoopSpan new];
    g_defaultNoopSpanContext = [OTNoopSpanContext new];
    g_defaultNoopTracer = [OTNoopTracer new];
}

- (id<OTSpan>)startSpan:(NSString*)operationName { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName tags:(NSDictionary*)tags { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName childOf:(id<OTSpanContext>)parent { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName childOf:(id<OTSpanContext>)parent tags:(NSDictionary*)tags { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName childOf:(id<OTSpanContext>)parent tags:(NSDictionary*)tags startTime:(NSDate*)startTime { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName references:(NSArray*)references tags:(NSDictionary*)tags startTime:(NSDate*)startTime { return g_defaultNoopSpan; }

- (bool)inject:(id<OTSpanContext>)span format:(NSString*)format carrier:(id)carrier { return true; }
- (bool)inject:(id<OTSpanContext>)span format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return true; }

- (id<OTSpanContext>)extract:(NSString*)format carrier:(id)carrier { return nil; }
- (id<OTSpanContext>)extract:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return nil; }

@end
