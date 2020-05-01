//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "SpaceShip.h"
#include "../../App/App.h"
#include "../../shapes/Rectangle.h"

SpaceShip::SpaceShip(): mNumMissiles(3), mDirection(0,-1) {}

const Rectangle SpaceShip::getBBox() const {
    return Rectangle(mOffset, mSpaceShipSprite.getBBox().getWidth(), mSpaceShipSprite.getBBox().getHeight());
}


void SpaceShip::init() {
    mSpriteSheet.load("AsteroidsSprites");

    mSpaceShipSprite.init(App::Singleton().getBasePath() + "../Assets/AsteroidsAnimations.txt", mSpriteSheet);
    mSpaceShipSprite.setAnimation("ship", true);

    mThrusterSprite.init(App::Singleton().getBasePath() + "../Assets/AsteroidsAnimations.txt", mSpriteSheet);
    mThrusterSprite.setAnimation("thrusters", true);


    Vec2D spaceshipCenter = {App::Singleton().width()/2 - mSpaceShipSprite.getBBox().getWidth()/2, App::Singleton().height()/2  - mSpaceShipSprite.getBBox().getHeight()/2};

    mSpaceShipSprite.setPosition(spaceshipCenter);

    mThrusterSprite.setPosition(spaceshipCenter);
    mThrusterSprite.moveBy(THRUSTER_OFFSET);

    mOffset = spaceshipCenter;
}

void SpaceShip::update(uint32_t dt) {
    mSpaceShipSprite.update(dt);
    mThrusterSprite.update(dt);
    for(auto missile : mCurrentMissiles) {
        if(missile) {
            missile->update(dt);
            if(missile->getPosition().GetY() < 0) {
                delete missile;
            }
        }

    }
}

void SpaceShip::draw(Screen& theScreen) {
    mSpaceShipSprite.draw(theScreen);
    mThrusterSprite.draw(theScreen);
    for(auto missile : mCurrentMissiles) {
        if(missile) missile->draw(theScreen);
    }
}

void SpaceShip::fireMissile() {
    if(mNumMissiles > 0) {
        Missile* mnoptrCurrentMissile = new Missile(mDirection,mOffset);
        mnoptrCurrentMissile->init();
        mCurrentMissiles.push_back(mnoptrCurrentMissile);
        --mNumMissiles;
    }

}