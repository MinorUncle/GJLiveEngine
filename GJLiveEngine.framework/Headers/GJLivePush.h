//
//  GJLivePush.h
//  GJCaptureTool
//
//  Created by mac on 17/2/23.
//  Copyright © 2017年 MinorUncle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GJLiveDefine.h"
#import <CoreVideo/CVImageBuffer.h>
#import <CoreMedia/CMTime.h>
#import <AVFoundation/AVFoundation.h>
@class UIView;
@class GJLivePush;
@class GJSticker;
@class GJAnimationSticker;
@class GJRealTimeSticker;
@class ARSCNView;
typedef void (^GJLiveARUpdateBlock)(void);
@protocol GJImageARScene <NSObject>
@required
@property (nonatomic, retain, readonly) ARSCNView *_Nullable scene;
@property (nonatomic, assign) NSInteger updateFps;
@property (readonly, nonatomic) BOOL    isRunning;
@property (nonatomic, assign) GJLiveARUpdateBlock _Nullable updateBlock;

- (AVCaptureDevicePosition)cameraPosition;
- (void)rotateCamera;

- (BOOL)startRun;
- (void)stopRun;
- (void)pause;
- (BOOL)resume;
@end

//GUInt32 mFps;
//GSize   mPushSize;
//GInt32  mVideoBitrate; //  bit/s
//
//GInt32              mAudioSampleRate;
//GInt32              mAudioChannel;
//GInt32              mAudioBitrate;

@interface GJPushConfigProtocol : NSObject
//required
@property(assign,nonatomic)NSInteger fps;
@property(assign,nonatomic)CGSize    pushSize;
@property(assign,nonatomic)NSInteger videoBitrate;
@property(assign,nonatomic)NSInteger audioSampleRate;
@property(assign,nonatomic)NSInteger audioChannel;
@property(assign,nonatomic)NSInteger audioBitrate;

//optional
@property(assign,nonatomic)GRational     maxVideoDrop;
@property(assign,nonatomic)NSInteger     lowQualityVideoBitrate;
@property(assign,nonatomic)GProfileLevel videoProfileLevel;
@property(assign,nonatomic)GEntropyMode  videoEntropyMode;
@end

@protocol GJLivePushDelegate <NSObject>
@required

- (void)livePush:(GJLivePush *_Nonnull)livePush mixFileFinish:(NSString *_Nonnull)path;
- (void)livePush:(GJLivePush *_Nonnull)livePush updatePushStatus:(GJPushSessionStatus *_Nonnull)status;
- (void)livePush:(GJLivePush *_Nonnull)livePush predictiveInfo:(GJNetPredictiveInfo *_Nonnull)predictiveInfo;
- (void)livePush:(GJLivePush *_Nonnull)livePush closeConnect:(GJPushSessionInfo *_Nonnull)info resion:(GJConnectCloceReason)reason;
- (void)livePush:(GJLivePush *_Nonnull)livePush connectSuccessWithElapsed:(GLong)elapsed;
- (void)livePush:(GJLivePush *_Nonnull)livePush dynamicVideoUpdate:(VideoDynamicInfo *_Nonnull)elapsed;
- (void)livePush:(GJLivePush *_Nonnull)livePush recodeFinish:(NSError *_Nullable)error;
- (void)livePush:(GJLivePush *_Nonnull)livePush errorType:(GJLiveErrorType)type infoDesc:(NSString *_Nonnull)info;
//-(void)livePush:(GJLivePush*)livePush pushPacket:(R_GJH264Packet*)packet;
//-(void)livePush:(GJLivePush*)livePush pushImagebuffer:(CVImageBufferRef)packet pts:(CMTime)pts;

@optional

@end

@interface GJOverlayAttribute : NSObject
//注意，frame的origin是中点
@property (assign, nonatomic) CGRect  frame;
@property (assign, nonatomic) CGFloat rotate;
//注意image更新后，每次该index循环都是更新后的图片
@property (retain, nonatomic) UIImage *_Nonnull image;

+ (instancetype _Nonnull)overlayAttributeWithImage:(UIImage *_Nonnull)image frame:(CGRect)frame rotate:(CGFloat)rotate;
@end
typedef void (^OverlaysUpdate)(NSInteger index, const GJOverlayAttribute *_Nullable ioAttr, BOOL *_Nonnull ioFinish);

@interface GJLivePush : NSObject

@property (nonatomic, weak) id<GJLivePushDelegate> _Nullable delegate;

@property (nonatomic, assign) BOOL videoMute;

#pragma mark video
@property (nonatomic, assign) GJCameraPosition cameraPosition;

@property (nonatomic, assign) BOOL previewMirror; //预览镜像，不镜像流

@property (nonatomic, assign) BOOL streamMirror; //流镜像，不影响预览

@property (nonatomic, assign) BOOL cameraMirror; //相机镜像，影响预览和流

@property (nonatomic, assign) GJInterfaceOrientation outOrientation;

@property (nonatomic, strong, readonly) UIView *_Nonnull previewView;

@property (nonatomic, assign, readonly) GJPushConfig pushConfig;

//只读，根据pushConfig中的push size自动选择最优.outOrientation 和 pushsize会改变改值，
@property (nonatomic, assign, readonly) CGSize captureSize;

//配置ar场景，开启ar模式，预览和推流前配置。scene= nil表示取消;
@property (nonatomic, retain) id<GJImageARScene> _Nullable ARScene;
//录屏直播
@property (nonatomic, retain) UIView *_Nullable captureView;

@property (nonatomic, assign) GJCaptureType captureType;

#pragma mark audio
@property (nonatomic, assign) BOOL audioMute;

@property (nonatomic, assign) BOOL measurementMode;

@property (nonatomic, assign) BOOL enableAec; //default NO

@property (nonatomic, assign) float inputVolume;

@property (nonatomic, assign) float mixVolume;

@property (nonatomic, assign) float masterOutVolume;

@property (nonatomic, assign, setter=enableReverb:) BOOL reverb;

@property (nonatomic, assign, setter=enableAudioInEarMonitoring:) BOOL audioInEarMonitoring;

@property (nonatomic, assign) BOOL mixFileNeedToStream;

/**
 美白：0-100
 */
@property (assign, nonatomic) NSInteger brightness;

/**
 磨皮：0-100
 */
@property (assign, nonatomic) NSInteger skinSoften;

/**
 皮肤红润：0--100
 */
@property (nonatomic, assign) NSInteger skinRuddy;

/**
 瘦脸：0--100
 */
@property (nonatomic, assign) NSInteger faceSlender; //

/**
 大眼：0--100
 */
@property (nonatomic, assign) NSInteger eyeEnlargement; //

- (void)startPreview;

- (void)stopPreview;

- (bool)startStreamPushWithUrl:(NSString *_Nonnull)url;

- (void)setPushConfig:(GJPushConfig)pushConfig;

- (void)stopStreamPush;

- (BOOL)startAudioMixWithFile:(NSURL *_Nonnull)fileUrl;

- (void)stopAudioMix;

- (BOOL)startUIRecodeWithRootView:(UIView *_Nonnull)view fps:(NSInteger)fps filePath:(NSURL *_Nonnull)file;

- (void)stopUIRecode;

- (UIImage *_Nullable)captureFreshDisplayImage;

-(void)addSticker:(GJSticker*)sticker;

-(void)removeStickerWithKey:(NSString*)key;

- (BOOL)startTrackingImageWithImages:(NSArray<UIImage*>*_Nonnull)images initFrame:(GCRect)frame;

- (void)stopTracking;

//- (void)videoRecodeWithPath:(NSString*)path;

-(BOOL)prepareVideoEffectWithBaseData:(NSString*)dataPath;
-(void)chanceVideoEffect;
- (BOOL) updateFaceStickTemplatePath:(NSString*)dataPath;


@end
