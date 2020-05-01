//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_BREAKOUT_H
#define LINES_BREAKOUT_H

#include "../Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"
#include <vector>

enum BreakOutStates {
    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME_OVER,
};

class BreakOut: public Game {
public:
    virtual void init(GameController& gameController) override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;
    virtual const std::string& getName() const override;

private:

    const int NUM_LIVES = 3;

    void resetGame(size_t toLevel = 0);

    BreakoutGameLevel& getCurrentLevel() {return mLevels[mCurrentLevel];}

    void setToServeState();

    bool isBallPastPaddle() const;
    void reduceLife();
    bool isGameOver() const { return mLives < 0;}

    const float INITIAL_BALL_SPEED = 100;
    const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100,-100);
    Paddle mPaddle;
    Ball mBall;
    LevelBoundary mLevelBoundary;
    std::vector<BreakoutGameLevel> mLevels;
    size_t  mCurrentLevel;
    BreakOutStates mGameState;
    int mLives;
    float mYCutoff;
};

#endif //LINES_BREAKOUT_H
