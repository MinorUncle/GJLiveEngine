//
//  GJOverlayAttribute.h
//  GJImageFilters
//
//  Created by melot on 2018/5/7.
//  Copyright © 2018年 MinorUncle. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreMedia/CMTime.h>
@class UIImage;
@class GJSticker;
typedef void(^StickerUpdate)(GJSticker* _Nonnull ioAttr,CMTime frameTs);

@interface GJSticker : NSObject<NSCopying>
@property(copy,nonatomic)NSString* _Nullable key;

//注意，frame的origin是中点,相对视频的位置，采用比例值，例如0.5表示中点。
@property(assign,nonatomic)CGRect frame;
@property(assign,nonatomic)CGFloat rotate;
@property(assign,nonatomic)float opaque;
@property(strong,nonatomic) UIImage* _Nullable  image;
+(instancetype _Nonnull )stickerWithImage:(UIImage* _Nonnull)image frame:(CGRect)frame rotate:(CGFloat)rotate opaque:(float)opaque;
@end

