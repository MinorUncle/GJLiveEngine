//
//  GJAnimationSticker.h
//  FMDB
//
//  Created by kyle on 2018/7/31.
//

#import "GJSticker.h"
#import "GJStickerAnimation.h"
@interface GJAnimationSticker : GJSticker


/**
 添加动画，每周type的动画只能添加一次，否则后面添加的会覆盖前面添加的。

 @param animation animation description
 */
-(void)addAnimation:(GJStickerAnimation*)animation;
-(void)removeAnimationWithType:(GJStickerAttributeType)type;

-(GJStickerAnimation*)animationWithType:(GJStickerAttributeType)type;
@end
