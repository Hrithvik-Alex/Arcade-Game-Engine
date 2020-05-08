//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_ACTOR_H
#define LINES_ACTOR_H

#include "../../graphics/AnimatedSprite.h"
#include "../../Utils/vec2D.h"
#include "PacmanGameUtils.h"
#include "../../shapes/Rectangle.h"
#include "../../graphics/color.h"
#include <string>
#include <stdint.h>

class Screen;
class SpriteSheet;

class Actor {
public:

    virtual ~Actor() {}
    virtual void init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = Color::White());
    virtual void update(uint32_t dt);
    virtual void draw(Screen& screen);

    virtual void stop();
    Rectangle getEatingBBox() const;

    inline bool isFinishedAnimation() const {return mSprite.isFinishedplayingAnimation();}
    inline const Rectangle getBoundingBox() const {return mSprite.getBBox();}
    inline void moveBy(const Vec2D& delta) {mSprite.moveBy(delta);}
    inline void moveTo(const Vec2D& position) {mSprite.setPosition(position);}
    inline Vec2D position() const {return mSprite.position();}
    inline PacmanMovement getMovementDirection() const {return mMovementDirection;}
    virtual inline void setMovementDirection(PacmanMovement direction) {mMovementDirection = direction;}
    inline const Color& getSpriteColor() const {return mSprite.getColor();}


protected:

    void setAnimation(const std::string& animationName, bool looped);

    inline void resetDelta() {mDelta = Vec2D::Zero;}
    inline void setMovementSpeed(uint32_t movementSpeed) {mMovementSpeed = movementSpeed;}

    AnimatedSprite mSprite;

private:
    Vec2D mDelta;
    PacmanMovement mMovementDirection;
    uint32_t mMovementSpeed;
    bool mUpdateSpriteOnUpdate;

};


#endif //LINES_ACTOR_H
