//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_ASTEROIDS_H
#define LINES_ASTEROIDS_H

#include "../Game.h"
#include "../../graphics/SpriteSheet.h"
#include "SpaceShip.h"

class Asteroids: public Game {
public:

    virtual void init(GameController& gameController) override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;
    virtual const std::string& getName() const override;
    
private:

    const int NUM_LIVES = 3;

    void resetGame();

    SpaceShip mSpaceShip;

};


#endif //LINES_ASTEROIDS_H
