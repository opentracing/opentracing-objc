#import <Foundation/Foundation.h>

#import "OTTracer.h"

@class OTNoopTracer : NSObject<OTTracer>

- (id<OTSpan>)startSpan:(NSString*)operationName;

- (id<OTSpan>)startSpan:(NSString*)operationName
		   tags:(NSDictionary*)tags;

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan;

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan
		   tags:(NSDictionary*)tags;

- (id<OTSpan>)startSpan:(NSString*)operationName
		 parent:(id<OTSpan>)parentSpan
		   tags:(NSDictionary*)tags
	      startTime:(NSDate*)startTime;


- (bool)inject:(id<OTSpan>)span
       	format:(NSString*)format
       carrier:(id)carrier;

- (bool)inject:(id<OTSpan>)span
       	format:(NSString*)format
       carrier:(id)carrier
	 error:(NSError* __autoreleasing *)outError;


- (id<OTSpan>)join:(NSString*)operationName
	    format:(NSString*)format
	   carrier:(id)carrier;

- (id<OTSpan>)join:(NSString*)operationName
	    format:(NSString*)format
	   carrier:(id)carrier
	     error:(NSError* __autoreleasing *)outError;

@end
