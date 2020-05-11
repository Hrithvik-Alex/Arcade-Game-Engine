//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_SPACESHIP_H
#define LINES_SPACESHIP_H

#include "../../graphics/AnimatedSprite.h"
#include "../../graphics/SpriteSheet.h"
#include "../../Utils/vec2D.h"
#include "Missile.h"
#include <stdint.h>
#include <vector>

class Rectangle;
class Screen;

class SpaceShip {
public:

    SpaceShip();
    ~SpaceShip();

    const Rectangle getBBox() const;

    void init(SpriteSheet* spriteSheet);
    void update(uint32_t dt);
    void draw(Screen& screen);

    void fireMissile();
    inline void setMovement(const bool movement) {mIsMoving = movement;}

    void explode();

    inline void rotateLeft(const bool rotate) {mRotatingLeft = rotate;}
    inline void rotateRight(const bool rotate) {mRotatingRight = rotate;}

    bool missileHit(const Rectangle& bbox);

private:

    static const int SHIP_VELOCITY = 100;
    const Vec2D THRUSTER_OFFSET = {0,15};
    AnimatedSprite mSpaceShipSprite;
    AnimatedSprite mThrusterSprite;
    Vec2D mOffset;
    Vec2D mDirection;
    bool mIsMoving;
    bool mRotatingRight;
    bool mRotatingLeft;
    bool mIsExplosion;
    int mNumMissiles;
    float mCurrentAngle;
    SpriteSheet* mSpriteSheet;
    std::vector<Missile*> mCurrentMissiles;
};


#endif //LINES_SPACESHIP_H
