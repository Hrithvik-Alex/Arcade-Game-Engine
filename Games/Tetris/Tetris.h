// Created by Hrithvik  Alex on 2020-04-19.

#ifndef LINES_TETRIS_H
#define LINES_TETRIS_H

#include "../Game.h"
#include "Grid.h"
#include "Tetromino.h"

class Screen;
class GameController;

class Tetris: public Game {
public:

    virtual void init(GameController& gameController) override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;
    virtual const std::string& getName() const override;


private:
    float mVelocity;
    void resetGame();
    Grid mGrid;
    Tetromino* mCurrentTetromino;
};

#endif //LINES_TETRIS_H
