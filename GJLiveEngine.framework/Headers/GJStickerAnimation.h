//
//  GJStickerAnimation.h
//  FMDB
//
//  Created by kyle on 2018/7/25.
//

#import <Foundation/Foundation.h>
#include "GJMediaTimingFunc.h"

typedef enum:NSUInteger{
    //默认CGPointZero，在视频帧范围的相对位置
    kIESStickerAttributeTypeCenter,
    //默认CGSizeZero，在视频帧大小的绝对大小，
    kIESStickerAttributeTypeSize,
    //0-360为一周，可以任意值 默认0
    kIESStickerAttributeTypeRotate,
    //默认1
    kIESStickerAttributeTypeOpaque,
    //默认nil
    kIESStickerAttributeTypeImage,
    //非动画属性，内部使用
    kIESStickerAttributeTypeCount,
}GJStickerAttributeType;

typedef enum:NSUInteger {
    //保持最后一帧动画
    kIESAnimationRepeatKeepLast,
    //保持第一帧动画
    kIESAnimationRepeatKeepFirst,
    //清零
    kIESAnimationRepeatRemove,
    //从第一帧开始重复动画
    kIESAnimationRepeatFromBegin,
    //从最后一帧开始反向动画
    kIESAnimationRepeatReverse,
}GJAnimationRepeatType;

@interface GJStickerAnimation : NSObject <NSCopying>

@property(assign,nonatomic)GJStickerAttributeType type;

@property(copy,nonatomic)NSArray* values;

@property(copy,nonatomic)NSArray<GJMediaTimingFunc*>* mediaTimingFuncs;

/**
 //CMTime格式，数组长度等于values长度，表示每个frameTs时间对应的属性值为value，frameTs为视频帧的绝对时间戳。
 */
@property(copy,nonatomic)NSArray< NSValue*>* frameTs;

@property(assign,nonatomic)BOOL isAbsoluteFrameTs;//是否绝对时间，No，表示相对添加到sticker的时间为0。

@property(assign,nonatomic)GJAnimationRepeatType repeatType;

@end
