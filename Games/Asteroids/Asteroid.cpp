//
// Created by Hrithvik  Alex on 2020-05-02.
//

#include "Asteroid.h"
#include "../../App/App.h"
#include "../../shapes/Rectangle.h"
#include "../../graphics/Screen.h"
#include <cmath>

Asteroid::Asteroid(): mSpriteSheet(nullptr), mAsteroidSize(static_cast<AsteroidSize>(rand() % 3)), mPosition(calculateRandomStart()), isCenter(true) {}

Asteroid::Asteroid(Vec2D position, AsteroidSize size): mSpriteSheet(nullptr), mAsteroidSize(size), mPosition(position), isCenter(false) {}

const Rectangle Asteroid::getBBox() const {
    assert(mSpriteSheet && mSpriteName != "");
    return Rectangle(mPosition, mSpriteSheet->getSprite(mSpriteName).width, mSpriteSheet->getSprite(mSpriteName).height);
}

void Asteroid::init(SpriteSheet* spriteSheet) {
    mSpriteSheet = spriteSheet;

    switch (mAsteroidSize) {
        case SMALL: {
            mSpriteName = "small_rock";
            mPoints = 100;
            break;
        }
        case MEDIUM: {
            mSpriteName = "medium_rock";
            mPoints = 50;
            break;
        }
        case LARGE: {
            mSpriteName = "big_rock";
            mPoints = 20;
            break;
        }
    }

    if(isCenter) {
        Vec2D center = Vec2D(App::Singleton().width()/2, App::Singleton().height()/2);
        Vec2D centerOffset = center - mPosition;
        mDirection = centerOffset.Normalize();
    } else {
        Vec2D dir = {0,-1};
        mDirection = dir.RotateResult(rand() % 360, Vec2D(0,0));
    }

}

void Asteroid::update(uint32_t dt) {
    float distance = MilliSecondsToSeconds(dt) * ASTEROID_VELOCITY;
    mPosition += mDirection * distance;
    mCurrentAngle += 0.001f * static_cast<float>(dt);
}

void Asteroid::draw(Screen& screen) {
    assert(mSpriteName != "");
    screen.Draw(*mSpriteSheet, mSpriteName, mPosition, Color::White(), true, mCurrentAngle);
}

Vec2D Asteroid::calculateRandomStart() {
    uint32_t circumference = App::Singleton().height()*2 + App::Singleton().width()*2;
    int randomIndex = rand() % circumference;
    if(0 <= randomIndex && randomIndex < App::Singleton().width()) {
        return Vec2D(randomIndex, 0);
    } else if (App::Singleton().width() <= randomIndex && randomIndex < App::Singleton().width() + App::Singleton().height()) {
        return Vec2D(App::Singleton().width(), randomIndex - App::Singleton().width());
    } else if (App::Singleton().width() + App::Singleton().height() <= randomIndex && randomIndex <= App::Singleton().width()*2 + App::Singleton().height()) {
        return Vec2D(App::Singleton().width() - (randomIndex - App::Singleton().width() - App::Singleton().height()), App::Singleton().height());
    } else {
        return Vec2D(0, randomIndex - (App::Singleton().width()*2 + App::Singleton().height()));
    }
}

std::vector<Asteroid*> Asteroid::destroy() {
    std::vector<Asteroid*> res;

    if(mAsteroidSize == LARGE) {
        res.push_back(new Asteroid(mPosition, MEDIUM));
        res.push_back(new Asteroid(mPosition, MEDIUM));
    } else if (mAsteroidSize == MEDIUM) {
        res.push_back(new Asteroid(mPosition, SMALL));
        res.push_back(new Asteroid(mPosition, SMALL));
        res.push_back(new Asteroid(mPosition, SMALL));
    }

    return res;
}