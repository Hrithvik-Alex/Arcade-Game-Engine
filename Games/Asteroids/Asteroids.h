//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_ASTEROIDS_H
#define LINES_ASTEROIDS_H

#include "../Game.h"
#include "../../graphics/SpriteSheet.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "../Score.h"
#include <vector>

class Asteroids: public Game {
public:

    Asteroids();
    ~Asteroids();

    virtual void init(GameController& gameController) override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;
    virtual const std::string& getName() const override;
    
private:

    const int NUM_LIVES = 3;
    const int ASTEROID_SPAWN_RATE = 3000;

    void resetGame();
    void reduceLife();
    bool isGameOver() const { return mLives < 0;}

    void cleanUpAsteroids();

    int mLives;
    int currentDt;
    SpaceShip mSpaceShip;
    std::vector<Asteroid*> mAsteroids;
    SpriteSheet mSpriteSheet;

    Score mScore;
};


#endif //LINES_ASTEROIDS_H
