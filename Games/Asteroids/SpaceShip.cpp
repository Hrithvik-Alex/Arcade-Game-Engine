//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "SpaceShip.h"
#include "../../App/App.h"
#include "../../shapes/Rectangle.h"

SpaceShip::SpaceShip(): mNumMissiles(3), mDirection(0,-1), mIsMoving(false) {}

SpaceShip::~SpaceShip() {
    for(auto& missile : mCurrentMissiles) {
        delete missile;
    }
}

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

    if(mIsMoving) {
        float distance = MilliSecondsToSeconds(dt) * SHIP_VELOCITY;
        mOffset += mDirection * distance;
        mSpaceShipSprite.setPosition(mOffset);
        mThrusterSprite.setPosition(mOffset + THRUSTER_OFFSET);
    }

    auto missileIt = mCurrentMissiles.begin();

    while(missileIt != mCurrentMissiles.end()) {
        (*missileIt)->update(dt);
        if((*missileIt)->getPosition().GetY() < 0) {
            delete (*missileIt);
            mCurrentMissiles.erase(missileIt);
            ++mNumMissiles;
        } else {
            ++missileIt;
        }
    }
}

void SpaceShip::draw(Screen& theScreen) {
    mSpaceShipSprite.draw(theScreen);
    if(mIsMoving) {
        mThrusterSprite.draw(theScreen);
    }
    for(auto& missile : mCurrentMissiles) {
        missile->draw(theScreen);
    }
}

void SpaceShip::fireMissile() {
    if(mNumMissiles > 0) {
        Missile* currentMissile = new Missile(mDirection,mOffset);
        currentMissile->init();
        mCurrentMissiles.push_back(currentMissile);
        --mNumMissiles;
    }

}
