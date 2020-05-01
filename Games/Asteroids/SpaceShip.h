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

    const Rectangle getBBox() const;

    void init();
    void update(uint32_t dt);
    void draw(Screen& screen);

    void fireMissile();


private:

    const Vec2D THRUSTER_OFFSET = {6,21};
    AnimatedSprite mSpaceShipSprite;
    AnimatedSprite mThrusterSprite;
    Vec2D mOffset;
    Vec2D mDirection;
    int mNumMissiles;
    SpriteSheet mSpriteSheet;
    std::vector<Missile*> mCurrentMissiles;
};


#endif //LINES_SPACESHIP_H
