//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "Missile.h"
#include "../../App/App.h"
#include "../../shapes/Rectangle.h"
#include "../../graphics/Screen.h"
#include "../../Utils/utils.h"

Missile::Missile(): Missile(Vec2D(0,-1), Vec2D(App::Singleton().width(), App::Singleton().height())) {}

Missile::Missile(const Vec2D direction, const Vec2D position): mDirection(direction), mPosition(position), mSpriteSheet(nullptr) {}

const Rectangle Missile::getBBox() const {
    return Rectangle(mPosition, mSprite.getBBox().getWidth(), mSprite.getBBox().getHeight());
}

void Missile::init(SpriteSheet* spriteSheet) {
    mSpriteSheet = spriteSheet;

    mSprite.init(App::Singleton().getBasePath() + "../Assets/AsteroidsAnimations.txt", *mSpriteSheet);
    mSprite.setAnimation("missile", true);
    mSprite.setPosition(mPosition);
}

void Missile::update(uint32_t dt) {
    float distance = MilliSecondsToSeconds(dt) * VELOCITY;
    mPosition += mDirection * distance;
    mSprite.update(dt);
    mSprite.setPosition(mPosition);
}

void Missile::draw(Screen& screen) {
    mSprite.draw(screen);

}
