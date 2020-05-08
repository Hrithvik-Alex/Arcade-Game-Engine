//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "AnimatedSprite.h"
#include "../shapes/Rectangle.h"
#include "Screen.h"
#include "SpriteSheet.h"

AnimatedSprite::AnimatedSprite():mPosition(Vec2D::Zero), mnoptrSpriteSheet(nullptr) {}

void AnimatedSprite::init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color) {
    mAnimationPlayer.init(animationsPath);
    mnoptrSpriteSheet = &spriteSheet;
    mColor = color;
}

void AnimatedSprite::update(uint32_t dt) {
    mAnimationPlayer.update(dt);
}

void AnimatedSprite::draw(Screen& theScreen, bool rotate, float angle) {
    AnimationFrame frame = mAnimationPlayer.getCurrentAnimationFrame();

    Color frameColor = frame.frameColor;

    if(!frame.frameColorSet) {
        frameColor = mColor;
    }

    if(rotate) {
        Sprite currentSprite = mnoptrSpriteSheet->getSprite(frame.frame);
        Vec2D centerOfSprite = mPosition + frame.offset + Vec2D(currentSprite.width/2,currentSprite.height/2);
        theScreen.Draw(*mnoptrSpriteSheet, frame.frame, mPosition + frame.offset, frameColor, true, angle, centerOfSprite);
    } else {
        theScreen.Draw(*mnoptrSpriteSheet, frame.frame, mPosition + frame.offset, frameColor);
    }


    if(frame.overlay.size() > 0) {
        theScreen.Draw(*mnoptrSpriteSheet, frame.overlay, mPosition + frame.offset, frame.overlayColor);
    }

}

void AnimatedSprite::setAnimation(const std::string& animationName, bool looped) {
    mAnimationPlayer.play(animationName, looped);
}

Vec2D AnimatedSprite::size() const {
    return mAnimationPlayer.getCurrentAnimationFrame().size;
}

void AnimatedSprite::stop() {
    mAnimationPlayer.stop();
}

const Rectangle AnimatedSprite::getBBox() const {
    Rectangle bbox = {mPosition, static_cast<unsigned int>(size().GetX()), static_cast<unsigned int>(size().GetY())};
    return bbox;
}