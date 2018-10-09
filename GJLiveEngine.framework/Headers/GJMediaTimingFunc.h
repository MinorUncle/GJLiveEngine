//
//  GJMediaTimingAdapter.h
//  FMDB
//
//  Created by kyle on 2018/7/26.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <QuartzCore/CAMediaTimingFunction.h>

@protocol GJMediaTimingTransformProtocol<NSObject>
-(float)transformFromTime:(float)frameTs;
@end

@interface GJMediaTimingFunc : NSObject<GJMediaTimingTransformProtocol>
-(float)transformFromTime:(float)frameTs;

@end


@interface GJMediaTimingBezierurveFunc : GJMediaTimingFunc
+(GJMediaTimingBezierurveFunc*)timingFuncWithControlPoint1:(CGPoint)point1 point2:(CGPoint)point2;

+(GJMediaTimingBezierurveFunc*)timingFuncWithName:(NSString*)funcName;
+(GJMediaTimingBezierurveFunc*)timingFuncWithFunc:(CAMediaTimingFunction*)func;

@end

@interface GJMediaTimingSpringFunc : GJMediaTimingFunc
//+(GJMediaTimingSpringFunc*)timingFuncWithTimingFunc:(float)func;

@end
