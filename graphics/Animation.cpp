//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "Animation.h"
#include "../Utils/FileCommandLoader.h"
#include <cassert>

Animation::Animation(): mSize(Vec2D::Zero), mSpriteSheetName(""), mAnimationName(""), mFPS(0) {}

AnimationFrame Animation::getAnimationFrame(uint32_t frameNum) const {
    AnimationFrame animationFrame;
    if(frameNum > mFrames.size()) {
        return animationFrame;
    }
    animationFrame.frame = mFrames[frameNum];
    if(frameNum < mFrameColors.size()) {
        animationFrame.frameColor = mFrameColors[frameNum];
        animationFrame.frameColorSet = 1;
    }

    if(mOverlay.size() > 0) {
        animationFrame.overlay = mOverlay;
    }
    if(frameNum < mOverlayColors.size()) {
        animationFrame.overlayColor = mOverlayColors[frameNum];
    }

    if(frameNum < mFrameOffsets.size()) {
        animationFrame.offset = mFrameOffsets[frameNum];
    }

    animationFrame.size = mSize;

    return animationFrame;
}

std::vector<Animation> Animation::LoadAnimations(const std::string& animationFilePath) {
    std::vector<Animation> animations;

    FileCommandLoader fileCommandLoader;

    Command animationCommand;
    animationCommand.command = "animation";
    animationCommand.parseFunc = [&](ParseFuncParams params) {
        Animation newAnimation;
        newAnimation.setName(FileCommandLoader::readString(params));
        animations.push_back(newAnimation);
    };

    fileCommandLoader.addCommand(animationCommand);


    Command spriteSheetCommand;
    spriteSheetCommand.command = "sprite_sheet";
    spriteSheetCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().setSpriteSheetName(FileCommandLoader::readString(params));
    };

    fileCommandLoader.addCommand(spriteSheetCommand);

    Command sizeCommand;
    sizeCommand.command = "size";
    sizeCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().setSize(FileCommandLoader::readSize(params));
    };

    fileCommandLoader.addCommand(sizeCommand);

    Command fpsCommand;
    fpsCommand.command = "fps";
    fpsCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().setFPS(FileCommandLoader::readInt(params));
    };

    fileCommandLoader.addCommand(fpsCommand);

    Command frameCommand;
    frameCommand.command = "frame_keys";
    frameCommand.commandType = COMMAND_MULTI_LINE;
    frameCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().addFrame(params.line);
    };

    fileCommandLoader.addCommand(frameCommand);

    Command overlayCommand;
    overlayCommand.command = "overlay";
    overlayCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().setOverlay(FileCommandLoader::readString(params));
    };

    fileCommandLoader.addCommand(overlayCommand);

    Command frameColorsCommand;
    frameColorsCommand.command = "frame_colors";
    frameColorsCommand.commandType = COMMAND_MULTI_LINE;
    frameColorsCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().addFrameColor(FileCommandLoader::readColor(params));
    };

    fileCommandLoader.addCommand(frameColorsCommand);

    Command overlayFrameColorsCommand;
    overlayFrameColorsCommand.command = "overlay_colors";
    overlayFrameColorsCommand.commandType = COMMAND_MULTI_LINE;
    overlayFrameColorsCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().addOverlayFrameColor(FileCommandLoader::readColor(params));
    };

    fileCommandLoader.addCommand(overlayFrameColorsCommand);

    Command frameOffsetsCommand;
    frameOffsetsCommand.command = "frame_offsets";
    frameOffsetsCommand.commandType = COMMAND_MULTI_LINE;
    frameOffsetsCommand.parseFunc = [&](ParseFuncParams params) {
        animations.back().addFrameOffset(FileCommandLoader::readSize(params));
    };

    fileCommandLoader.addCommand(frameOffsetsCommand);

    assert(fileCommandLoader.loadFile(animationFilePath));

    return animations;
}
