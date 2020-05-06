//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "SpaceShip.h"
#include "../../App/App.h"
#include "../../shapes/Rectangle.h"
#include "../../Utils/utils.h"

SpaceShip::SpaceShip(): mNumMissiles(3), mDirection(0,-1), mIsMoving(false), mIsExplosion(false), mSpriteSheet(nullptr) {}

SpaceShip::~SpaceShip() {
    for(auto& missile : mCurrentMissiles) {
        delete missile;
    }
}

const Rectangle SpaceShip::getBBox() const {
    return Rectangle(mOffset, mSpaceShipSprite.getBBox().getWidth(), mSpaceShipSprite.getBBox().getHeight());
}

void SpaceShip::init(SpriteSheet* spriteSheet) {
    mSpriteSheet = spriteSheet;

    mSpaceShipSprite.init(App::Singleton().getBasePath() + "../Assets/AsteroidsAnimations.txt", *mSpriteSheet);
    mSpaceShipSprite.setAnimation("ship", true);

    mThrusterSprite.init(App::Singleton().getBasePath() + "../Assets/AsteroidsAnimations.txt", *mSpriteSheet);
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

    if(mIsMoving && !mIsExplosion) {
        float distance = MilliSecondsToSeconds(dt) * SHIP_VELOCITY;
        mOffset += mDirection * distance;
        mSpaceShipSprite.setPosition(mOffset);
        mThrusterSprite.setPosition(mOffset + THRUSTER_OFFSET);

        if(mOffset.GetX() < 0) {
            mOffset += Vec2D(App::Singleton().width(), 0);
        } else if(mOffset.GetX() > App::Singleton().width()) {
            mOffset -= Vec2D(App::Singleton().width(), 0);
        }
        if(mOffset.GetY() < 0) {
            mOffset += Vec2D(0,App::Singleton().height());
        } else if(mOffset.GetY() > App::Singleton().height()) {
            mOffset -= Vec2D(0,App::Singleton().height());
        }
    }

    if(mRotatingLeft) {
        mDirection.Rotate(-10*dt,Vec2D::Zero);
    }

    if(mRotatingRight) {
        mDirection.Rotate(10*dt,Vec2D::Zero);
    }

    if (mIsExplosion) {
        if(mSpaceShipSprite.isFinishedplayingAnimation()) {
            mIsExplosion = false;
            mSpaceShipSprite.setAnimation("ship", true);
            mOffset += Vec2D(5,5);
        }
    }

    auto missileIt = mCurrentMissiles.begin();

    while(missileIt != mCurrentMissiles.end()) {
        (*missileIt)->update(dt);
        if(outOfBounds((*missileIt)->getPosition())) {
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
    if(mIsMoving && !mIsExplosion) {
        mThrusterSprite.draw(theScreen);
    }
    for(auto& missile : mCurrentMissiles) {
        missile->draw(theScreen);
    }
}

void SpaceShip::fireMissile() {
    if(!mIsExplosion) {
        if(mNumMissiles > 0) {
            Missile* currentMissile = new Missile(mDirection,mOffset);
            currentMissile->init(mSpriteSheet);
            mCurrentMissiles.push_back(currentMissile);
            --mNumMissiles;
        }
    }
}

void SpaceShip::explode() {
    mIsExplosion = true;
    mSpaceShipSprite.setAnimation("explosion", false);
    mCurrentMissiles.clear();
    mNumMissiles = 3;
    mDirection = Vec2D(0,-1);
    mOffset += Vec2D(-5,-5);
}

bool SpaceShip::missileHit(const Rectangle& bbox) {
    auto missile = mCurrentMissiles.begin();
    while (missile != mCurrentMissiles.end()) {
        if((*missile)->getBBox().intersects(bbox)) {
            delete (*missile);
            mCurrentMissiles.erase(missile);
            ++mNumMissiles;
            return true;
        }
        ++missile;
    }
    return false;
}