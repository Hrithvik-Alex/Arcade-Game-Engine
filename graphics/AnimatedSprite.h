//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_ANIMATEDSPRITE_H
#define LINES_ANIMATEDSPRITE_H

#include "../Utils/vec2D.h"
#include "AnimationPlayer.h"
#include "color.h"
#include <stdint.h>
#include <string>

class Rectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite {
public:

    AnimatedSprite();
    void init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());
    void update(uint32_t dt);
    void draw(Screen& theScreen, bool rotate = false, float angle = 0.0f);

    void setAnimation(const std::string& animationName, bool looped);
    Vec2D size() const;
    void stop();
    const Rectangle getBBox() const;

    inline Vec2D position() const {return mPosition;}
    inline void setPosition(const Vec2D& position) {mPosition = position;}
    inline void moveBy(const Vec2D& delta) {mPosition += delta;}
    inline bool isFinishedplayingAnimation() const {return mAnimationPlayer.isFinishedPlaying();}
    inline const Color& getColor() const {return mColor;}
    inline const SpriteSheet* getSpriteSheet() const {return mnoptrSpriteSheet;}

private:

    const SpriteSheet* mnoptrSpriteSheet;
    AnimationPlayer mAnimationPlayer;
    Vec2D mPosition;
    Color mColor;
};


#endif //LINES_ANIMATEDSPRITE_H
