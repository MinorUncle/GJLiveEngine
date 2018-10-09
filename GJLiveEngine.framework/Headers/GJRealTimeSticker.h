//
//  GJRealTimeSticker.h
//  GJLiveEngine
//
//  Created by kyle on 2018/10/9.
//  Copyright © 2018年 MinorUncle. All rights reserved.
//

#import "GJSticker.h"

NS_ASSUME_NONNULL_BEGIN
typedef void(^UpdateStickerBlock)(GJSticker* sticker);
@interface GJRealTimeSticker : GJSticker
@property(nonatomic,copy)UpdateStickerBlock updateBlock;
@end

NS_ASSUME_NONNULL_END
