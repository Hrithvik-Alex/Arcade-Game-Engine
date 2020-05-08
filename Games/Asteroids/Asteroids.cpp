//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "Asteroids.h"
#include "Missile.h"
#include "../../Input/GameController.h"
#include "../../shapes/Rectangle.h"
#include "../../App/App.h"


/*
 * Player/Spaceship
 *  3 lives
 *  spins
 *  shoots missile
 *  dies when colliding with asteroid
 *  wraps around screen
 *  3 missiles at a time
 *
 * Missile
 *   constant velocity
 *   shoots in one direction straight
 *   disappears once colliding with asteroid or out of screen
 *
 * Asteroid
 *  3 different sizes
 *  breaking one transforms it into smaller sizes
 *  converges to middle from random directions of screen
 *
 * Grid
 *
 *
 * */

 Asteroids::Asteroids(): mScore(Rectangle(Vec2D(App::Singleton().width()-50,10), 40, 20), App::Singleton().getFont()) {}

Asteroids::~Asteroids() {
    for(auto& asteroid : mAsteroids) {
        delete asteroid;
    }
}


void Asteroids::init(GameController& gameController){
    gameController.clearAll();

    resetGame();

    mSpriteSheet.load("AsteroidsSprites");

    mSpaceShip.init(&mSpriteSheet);


    ButtonAction fireAction;
    fireAction.key = GameController::ActionKey();
    fireAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mSpaceShip.fireMissile();
        }
    };

    gameController.addInputActionForKey(fireAction);

    ButtonAction moveAction;
    moveAction.key = GameController::UpKey();
    moveAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mSpaceShip.setMovement(true);
        } else {
            mSpaceShip.setMovement(false);
        }
    };

    gameController.addInputActionForKey(moveAction);

    ButtonAction leftAction;
    leftAction.key = GameController::LeftKey();
    leftAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mSpaceShip.rotateLeft(true);
        } else {
            mSpaceShip.rotateLeft(false);
        }
    };

    gameController.addInputActionForKey(leftAction);

    ButtonAction rightAction;
    rightAction.key = GameController::RightKey();
    rightAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mSpaceShip.rotateRight(true);
        } else {
            mSpaceShip.rotateRight(false);
        }
    };

    gameController.addInputActionForKey(rightAction);

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            App::Singleton().popScene();
        }

    };

    gameController.addInputActionForKey(backAction);
}

void Asteroids::update(uint32_t dt){
    currentDt += dt;
    mSpaceShip.update(dt);
    if(currentDt >= ASTEROID_SPAWN_RATE) {
        Asteroid* asteroid = new Asteroid();
        asteroid->init(&mSpriteSheet);
        mAsteroids.push_back(asteroid);
        currentDt -= ASTEROID_SPAWN_RATE;
    }

    int length = mAsteroids.size();
    for(int i = 0; i < length; ++i) {

        mAsteroids[i]->update(dt);

        if(outOfBounds(mAsteroids[i]->getBBox().getTopLeftPoint()) && outOfBounds(mAsteroids[i]->getBBox().getBottomRightPoint())) {
            delete mAsteroids[i];
            mAsteroids[i] = nullptr;
            continue;
        }

        if(mSpaceShip.getBBox().intersects(mAsteroids[i]->getBBox())) {
            reduceLife();
            break;
        }


        bool missileHit = mSpaceShip.missileHit(mAsteroids[i]->getBBox());
        if(missileHit) {
            std::vector<Asteroid*> nextAsteroids = mAsteroids[i]->destroy();
            for(auto& newAsteroid : nextAsteroids) {
                newAsteroid->init(&mSpriteSheet);
                mAsteroids.push_back(newAsteroid);
            }

            mScore.addToScore(mAsteroids[i]->getPoints());

            delete mAsteroids[i];
            mAsteroids[i] = nullptr;
        }

    }

    if(mLives < 0) {
        resetGame();
    }

    cleanUpAsteroids();
}

void Asteroids::draw(Screen& screen){
    mSpaceShip.draw(screen);
    mScore.draw(screen);
    for(auto& asteroid : mAsteroids) {
        asteroid->draw(screen);
    }

    Vec2D lifeVector = Vec2D(7, App::Singleton().height() - 10);
    for(int i = 0; i < mLives; ++i) {
        screen.Draw(mSpriteSheet, "space_ship", lifeVector);
        lifeVector += Vec2D(17, 0);
    }
}

const std::string& Asteroids::getName() const {
    static std::string name = "Asteroids";
    return name;
}

void Asteroids::resetGame() {
    mLives = NUM_LIVES;
    mScore.resetScore();
}

void Asteroids::reduceLife() {
    mSpaceShip.explode();
    if(mLives >= 0) {
        --mLives;
    }

    for(int i = 0; i < mAsteroids.size(); ++i) {
        delete mAsteroids[i];
        mAsteroids[i] = nullptr;
    }
    mAsteroids.clear();
}

void Asteroids::cleanUpAsteroids() {
    auto it = mAsteroids.begin();
    while(it != mAsteroids.end()) {
        if((*it) && (*it)->isInitialized()) {
            ++it;
        } else {
            mAsteroids.erase(it);
        }
    }
}