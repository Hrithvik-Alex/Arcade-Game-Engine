//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_ANIMATION_H
#define LINES_ANIMATION_H

#include <string>
#include <vector>
#include "../Utils/vec2D.h"
#include "../Utils/utils.h"
#include "../graphics/color.h"

struct AnimationFrame {
    std::string frame = "";
    std::string overlay = "";
    Color frameColor = Color::White();
    Color overlayColor = Color::White();
    Vec2D size;
    Vec2D offset = Vec2D::Zero;
    int frameColorSet = 0;

};

class Animation {
public:
    Animation();

    AnimationFrame getAnimationFrame(uint32_t frameNum) const;

    inline void addFrame(const std::string& frame) {mFrames.push_back(frame);}
    inline void addFrameColor(const Color& color) {mFrameColors.push_back(color);}
    inline void addOverlayFrameColor(const Color& color) {mOverlayColors.push_back(color);}
    inline void addFrameOffset(const Vec2D& offset) {mFrameOffsets.push_back(offset);}

    inline void setSpriteSheetName(const std::string& spriteSheetName) {mSpriteSheetName = spriteSheetName;}
    inline const std::string& getSpriteSheetName() const {return mSpriteSheetName;}

    inline void setName(const std::string& animationName) {mAnimationName = animationName;}
    inline const std::string& getName() const {return mAnimationName;}

    inline Vec2D size() const {return mSize;}
    inline void setSize(const Vec2D& size) {mSize = size;}

    inline void setFPS(int fps) {mFPS = fps;}
    inline int fps() const {return mFPS;}

    inline void setOverlay(const std::string& overlayName) {mOverlay = overlayName;}
    inline const std::string& overlayName() const {return mOverlay;}

    size_t numFrames() const {return mFrames.size();}
    size_t numFrameColors() const {return mFrameColors.size();}
    size_t numOverlayColors() const {return mOverlayColors.size();}
    size_t numFrameOffsets() const {return mFrameOffsets.size();}

    static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);

private:
    std::string mAnimationName;
    std::string mSpriteSheetName;
    std::string mOverlay;
    std::vector<std::string> mFrames;
    std::vector<Color> mFrameColors;
    std::vector<Color> mOverlayColors;
    std::vector<Vec2D> mFrameOffsets;
    Vec2D mSize;
    int mFPS;
};

#endif //LINES_ANIMATION_H
