#import "OTTracer.h"

NSString* const OTFormatTextMap = @"text_map";
NSString* const OTFormatHTTPHeaders = @"http_headers";
NSString* const OTFormatBinary = @"binary";

NSString *const OTErrorDomain = @"opentracing.io";
NSInteger OTUnsupportedFormatCode = 1;
NSInteger OTInvalidCarrierCode = 2;
NSInteger OTSpanContextCorruptedCode = 3;
