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
- (void)forEachBaggageItem:(BOOL (^) (NSString* key, NSString* value))callback {}
@end

@interface OTNoopSpan : NSObject<OTSpan>
@end

@implementation OTNoopSpan
- (id<OTTracer>)tracer { return g_defaultNoopTracer; }
- (id<OTSpanContext>)context { return g_defaultNoopSpanContext; }
- (void)setOperationName:(NSString*)operationName {}
- (void)setTag:(NSString*)key value:(NSString *)value {}
- (void)setTag:(NSString*)key numberValue:(NSNumber *)value {}
- (void)setTag:(NSString*)key boolValue:(BOOL)value {}
- (void)log:(NSDictionary<NSString*, NSObject*>*)fields {}
- (void)log:(NSDictionary<NSString*, NSObject*>*)fields timestamp:(nullable NSDate*)timestamp {}
- (void)logEvent:(NSString*)eventName {}
- (void)logEvent:(NSString*)eventName payload:(NSObject*)payload {}
- (void)log:(NSString*)eventName timestamp:(NSDate*)timestamp payload:(NSObject*)payload {}
- (id<OTSpan>)setBaggageItem:(NSString*)key value:(NSString*)value { return self; }
- (NSString*)getBaggageItem:(NSString*)key { return nil; }
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

- (BOOL)inject:(id<OTSpanContext>)span format:(NSString*)format carrier:(id)carrier { return true; }
- (BOOL)inject:(id<OTSpanContext>)span format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return true; }

- (id<OTSpanContext>)extractWithFormat:(NSString*)format carrier:(id)carrier { return nil; }
- (id<OTSpanContext>)extractWithFormat:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return nil; }

@end
