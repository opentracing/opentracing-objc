#import "OTNoop.h"

@implementation OTNoopTracer

- (id<OTSpan>)startSpan:(NSString*)operationName {
    return nil;
}

- (id<OTSpan>)startSpan:(NSString*)operationName
		   tags:(NSDictionary*)tags {
    return nil;
}

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan {
    return nil;
}

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan
		   tags:(NSDictionary*)tags {
    return nil;
}

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan
		   tags:(NSDictionary*)tags
	      startTime:(NSDate*)startTime {
    return nil;
}


- (bool)inject:(id<OTSpan>)span
       	format:(NSString*)format
       carrier:(id)carrier {
    return false;
}

- (bool)inject:(id<OTSpan>)span
       	format:(NSString*)format
       carrier:(id)carrier
	 error:(NSError* __autoreleasing *)outError {
    return false;
}


- (id<OTSpan>)join:(NSString*)operationName
	    format:(NSString*)format
	   carrier:(id)carrier {
    return nil;
}

- (id<OTSpan>)join:(NSString*)operationName
	    format:(NSString*)format
	   carrier:(id)carrier
	     error:(NSError* __autoreleasing *)outError {
    return nil;
}

@end
