//
// Created by Hrithvik  Alex on 2020-05-08.
//

#include "Actor.h"
#include "../../Utils/utils.h"
#include <cmath>

void Actor::init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor) {
    mMovementDirection = PACMAN_MOVEMENT_NONE;
    mSprite.init(animationsPath, spriteSheet, spriteColor);
    mUpdateSpriteOnUpdate = updateSpriteOnMovement;
    mMovementSpeed = movementSpeed;
    mDelta = Vec2D::Zero;
}
void Actor::update(uint32_t dt) {
    if(mMovementDirection != PACMAN_MOVEMENT_NONE) {
        Vec2D delta = Vec2D::Zero;
        delta = getMovementVector(mMovementDirection) * mMovementSpeed;

        mDelta += delta * MilliSecondsToSeconds(dt);

        if(fabsf(mDelta.GetX()) >= 1) {
            int dx = int(fabsf(mDelta.GetX()));

            if(mDelta.GetX() < 0) {
                mSprite.moveBy(Vec2D(-dx,0));
                mDelta.SetX(mDelta.GetX() + dx);
            } else {
                mSprite.moveBy(Vec2D(dx,0));
                mDelta.SetX(mDelta.GetX() - dx);
            }
        } else if(fabsf(mDelta.GetY()) >= 1) {
            int dy = int(fabsf(mDelta.GetY()));

            if(mDelta.GetY() < 0) {
                mSprite.moveBy(Vec2D(-dy,0));
                mDelta.SetY(mDelta.GetY() + dy);
            } else {
                mSprite.moveBy(Vec2D(dy,0));
                mDelta.SetX(mDelta.GetY() - dy);
            }
        }

        mSprite.update(dt);
    }

    if(mUpdateSpriteOnUpdate && mMovementDirection == PACMAN_MOVEMENT_NONE) {
        mSprite.update(dt);
    }

}

void Actor::draw(Screen& screen) {
    mSprite.draw(screen);
}

void Actor::stop() {
    setMovementDirection(PACMAN_MOVEMENT_NONE);
    mSprite.stop();
}

Rectangle Actor::getEatingBBox() const {
    return Rectangle::inset(getBoundingBox(), Vec2D(3,3));
}

void Actor::setAnimation(const std::string& animationName, bool looped) {
    mSprite.setAnimation(animationName, looped);
}
