//
// Created by Hrithvik  Alex on 2020-04-30.
//

#include "Asteroids.h"
#include "../../Input/GameController.h"


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



void Asteroids::init(GameController& gameController){
    gameController.clearAll();

    mSpaceShip.init();

    ButtonAction fireAction;
    fireAction.key = GameController::ActionKey();
    fireAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mSpaceShip.fireMissile();
        }
    };

    gameController.addInputActionForKey(fireAction);

}

void Asteroids::update(uint32_t dt){
    mSpaceShip.update(dt);
}

void Asteroids::draw(Screen& screen){
    mSpaceShip.draw(screen);
}

const std::string& Asteroids::getName() const {
    static std::string name = "Asteroids";
    return name;
}
