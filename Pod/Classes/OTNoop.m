#import "OTNoop.h"
#import "OTSpan.h"

@class OTNoopSpan;

// Initialized in OTNoopTracer.initialize:
static OTNoopTracer* g_defaultNoopTracer;
static OTNoopSpan* g_defaultNoopSpan;

@interface OTNoopSpan : NSObject<OTSpan>
@end

@implementation OTNoopSpan
- (id<OTTracer>)tracer { return g_defaultNoopTracer; }
- (void)setOperationName:(NSString*)operationName {}
- (void)setTag:(NSString*)key value:(NSString*)value {}
- (void)logEvent:(NSString*)eventName {}
- (void)logEvent:(NSString*)eventName payload:(NSObject*)payload {}
- (void)log:(NSString*)eventName timestamp:(NSDate*)timestamp payload:(NSObject*)payload {}
- (void)setBaggageItem:(NSString*)key value:(NSString*)value {}
- (NSString*)getBaggageItem:(NSString*)key { return nil; }
- (void) finish {}
- (void) finishWithTime:(NSDate*)finishTime {}
@end

@implementation OTNoopTracer

+ (void)initialize {
    g_defaultNoopSpan = [OTNoopSpan new];
    g_defaultNoopTracer = [OTNoopTracer new];
}

- (id<OTSpan>)startSpan:(NSString*)operationName { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName tags:(NSDictionary*)tags { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName parent:(id<OTSpan>)parentSpan { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName parent:(id<OTSpan>)parentSpan tags:(NSDictionary*)tags { return g_defaultNoopSpan; }
- (id<OTSpan>)startSpan:(NSString*)operationName parent:(id<OTSpan>)parentSpan tags:(NSDictionary*)tags startTime:(NSDate*)startTime { return g_defaultNoopSpan; }

- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier { return true; }
- (bool)inject:(id<OTSpan>)span format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return true; }

- (id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier { return nil; }
- (id<OTSpan>)join:(NSString*)operationName format:(NSString*)format carrier:(id)carrier error:(NSError* __autoreleasing *)outError { return nil; }

@end
