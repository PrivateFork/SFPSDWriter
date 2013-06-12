//
//  SFPSDLayer.h
//  SFPSDWriter
//
//  Created by Konstantin Erokhin on 06/06/13.
//  Copyright (c) 2013 Shiny Frog. All rights reserved.
//
//  Inspired by PSDWriter by Ben Gotow ( https://github.com/bengotow/PSDWriter )
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#import "SFPSDLayerBlendModes.h"

@interface SFPSDLayer : NSObject
{
}

/** The size of the document the layer will be insert into. */
@property (nonatomic, assign) CGSize documentSize;

/** The name of the layer. */
@property (nonatomic, strong) NSString *name;

/** 
 * The image data in RGBA or RGB format, depending on whether the PSDWriter.layerChannelCount
 * is set to 4 or 3, respectively. */
@property (nonatomic, strong) NSData *imageData;

/** The opacity of the layer between 0 and 1. */
@property (nonatomic, assign) float opacity;

/**
 * The rectangle the layer should be placed within in the PSD. Note that scaling is not currently
 * supported, so you should really only adjust the origin of this rect to move the imageData around
 * within the PSD. */
@property (nonatomic, assign) CGRect rect;

/** Number of channels of the layer. Defaults to 4. */
@property (nonatomic, assign) NSInteger channelCount;

/** 
 * Allows you to automatically vertically flip the image data when it's being
 * written to PSD. This is important if the source images are coming from OpenGL or
 * another drawing system with an inverted coordinate system. */
@property (nonatomic, assign) BOOL shouldFlipLayerData;

/** 
 * Allows you to automatically unpremultiply the image data. Premultiplication is
 * a process by which the R,G, and B values are multiplied by the alpha. Setting this
 * to YES will cause RGB to be divided by A. You'll know you need to do this if the
 * image comes out darker than you expect. */
@property (nonatomic, assign) BOOL shouldUnpremultiplyLayerData;

/** Layer blend mode. */
@property (nonatomic, strong) NSString *blendMode;

/**
 * Writes the Layer Information Section inside the mutable data (the first part of the "Layer info"
 * section of the "Layer and mask information section")
 *
 * Adobe documentation: Information about each layer. See Layer records describes the structure of
 * this information for each layer. */
- (void)writeLayerInformationOn:(NSMutableData *)layerInformation;

/** 
 * Writes the "Channel Image Data" inside the mutable data (the second part of the "Layer info"
 * section of the "Layer and mask information section")
 *
 * Adobe documentation: Channel image data. Contains one or more image data records (see See Channel
 * image data for structure) for each layer. The layers are in the same order as in the layer
 * information (previous row of this table). */
- (void)writeLayerChannelsOn:(NSMutableData *)layerInformation;

@end

@interface SFPSDLayer (Protected)

/** Returns an array of the channels composing the layer. */
- (NSArray *)layerChannels;

/** Writes the name on data. Tipically used in the "extra data field". */
- (void)writeNameOn:(NSMutableData *)data withPadding:(int)padding;

/** Writes the unicode name on data. Tipically used in the "extra data field". */
- (void)writeUnicodeNameOn:(NSMutableData *)data;

/** Extra layer information data. Has to be overridden in the extended classes (i.e. in the
 * PSDGroupOpeningLayer and PSDGroupClosingLayer). */
- (NSData *)extraLayerInformation;

@end