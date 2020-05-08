//
// Created by Hrithvik  Alex on 2020-05-02.
//

#ifndef LINES_ASTEROID_H
#define LINES_ASTEROID_H

#include "../../Utils/vec2D.h"
#include "../../graphics/AnimatedSprite.h"
#include "../../graphics/SpriteSheet.h"
#include <stdint.h>
#include <vector>

enum AsteroidSize {
    SMALL = 0,
    MEDIUM,
    LARGE
};

class Screen;
class Rectangle;

class Asteroid {
public:
    Asteroid();
    Asteroid(Vec2D position, AsteroidSize size);

    const Rectangle getBBox() const;

    void init(SpriteSheet* spriteSheet);
    void update(uint32_t dt);
    void draw(Screen& screen);

    std::vector<Asteroid*> destroy();

    bool isInitialized() const {return mSpriteName != "";}

    inline int getPoints() {return mPoints;}

private:

    Vec2D calculateRandomStart();

    static const int ASTEROID_VELOCITY = 100;
    AsteroidSize mAsteroidSize;
    Vec2D mDirection;
    Vec2D mPosition;
    std::string mSpriteName;
    SpriteSheet* mSpriteSheet;

    int mPoints;
    float mCurrentAngle;

    bool isCenter;

};


#endif //LINES_ASTEROID_H
