//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_MISSILE_H
#define LINES_MISSILE_H

#include "../../Utils/vec2D.h"
#include "../../graphics/AnimatedSprite.h"
#include "../../graphics/SpriteSheet.h"

class Rectangle;
class Screen;

class Missile {
public:

    Missile();
    Missile(const Vec2D direction, const Vec2D position);

    const Rectangle getBBox() const;

    void init();
    void update(uint32_t dt);
    void draw(Screen& screen);

    inline const Vec2D getPosition() const {return mPosition;}

private:
    static const int VELOCITY = 100;
    Vec2D mDirection;
    Vec2D mPosition;
    AnimatedSprite mSprite;
    SpriteSheet mSpriteSheet;

};


#endif //LINES_MISSILE_H