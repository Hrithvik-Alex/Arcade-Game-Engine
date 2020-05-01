//
// Created by Hrithvik  Alex on 2020-04-09.
//

#include "BreakOut.h"
#include "../../Input/InputAction.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"
#include <iostream>
#include "../../shapes/Circle.h"


void BreakOut::init(GameController& gameController) {
    gameController.clearAll();


    resetGame();

    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t dt, InputState state) {
        if(mGameState == IN_SERVE) {
            if(GameController::IsPressed(state)) {
                mGameState = IN_PLAY;

                if(mPaddle.isMovingLeft()) {
                    mBall.setVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                } else {
                    mBall.setVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
            }
        } else if(mGameState == IN_GAME_OVER) {
            if(GameController::IsPressed(state)) {
                resetGame();
            }
        }
    };

    gameController.addInputActionForKey(serveAction);

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE) {
            if (GameController::IsPressed(state)) {
                mPaddle.setMovementDirection(PaddleDirection::LEFT);
            } else {
                mPaddle.unsetMovementDirection(PaddleDirection::LEFT);
            }
        }
    };

    gameController.addInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE) {
            if(GameController::IsPressed(state)) {
                mPaddle.setMovementDirection(PaddleDirection::RIGHT);
            } else {
                mPaddle.unsetMovementDirection(PaddleDirection::RIGHT);
            }
        }
    };

    gameController.addInputActionForKey(rightKeyAction);

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state) {
        if(mGameState == IN_SERVE || mGameState == IN_GAME_OVER) {
            if(GameController::IsPressed(state)) {
                App::Singleton().popScene();
            }
        }
    };

    gameController.addInputActionForKey(backAction);


}

void BreakOut::update(uint32_t dt) {
    if(mGameState == IN_SERVE) {
        mPaddle.update(dt, mBall);
        setToServeState();
    } else if (mGameState == IN_PLAY) {
        mBall.update(dt);
        mPaddle.update(dt, mBall);

        BoundaryEdge edge;

        if(mPaddle.bounce(mBall)) {
            return;
        };

        if(mLevelBoundary.hasCollided(mBall, edge)) {
            mBall.bounce(edge);
            return;
        }

        getCurrentLevel().update(dt, mBall);

        if(isBallPastPaddle()) {
            reduceLife();
            if(!isGameOver()) {
                setToServeState();
            } else {
                mGameState = IN_GAME_OVER;
            }
        } else if(getCurrentLevel().isLevelComplete()) {
            mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
            resetGame(mCurrentLevel);
        }


    }
}

void BreakOut::draw(Screen& screen) {
    mBall.draw(screen);
    mPaddle.draw(screen);
    getCurrentLevel().draw(screen);
    screen.Draw(mLevelBoundary.getRectangle(), Color::White());
    Circle lifeCircle = {Vec2D(7, App::Singleton().height() - 10), 5};

    for(int i = 0; i < mLives; ++i) {
        screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
        lifeCircle.moveBy(Vec2D(17, 0));
    }
}

const std::string& BreakOut::getName() const {
    static std::string name = "Break Out!";
    return name;
}

void BreakOut::resetGame(size_t toLevel) {
    mLevels = BreakoutGameLevel::LoadLevelsFromFile(App::getBasePath() + "../Assets/BreakoutLevels.txt");
    mYCutoff = App::Singleton().height() - 2*Paddle::PADDLE_HEIGHT;
    mLives = NUM_LIVES;
    mCurrentLevel = toLevel;
    Rectangle paddleRect = {Vec2D(App::Singleton().width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    Rectangle levelBoundary = {Vec2D::Zero, App::Singleton().width(), App::Singleton().height()};

    mLevelBoundary = {levelBoundary};

    mPaddle.init(paddleRect, levelBoundary);
    mBall.moveTo(Vec2D(App::Singleton().width()/2, App::Singleton().height() *0.75f));
    setToServeState();
}

void BreakOut::setToServeState() {
    mGameState = IN_SERVE;
    mBall.stop();

    mBall.moveTo(Vec2D(mPaddle.getRectangle().getCenter().GetX(), mPaddle.getRectangle().getTopLeftPoint().GetY() - mBall.getRadius()-1));


}

bool BreakOut::isBallPastPaddle() const {
    return mBall.getPosition().GetY() > mYCutoff;
}

void BreakOut::reduceLife() {
    if(mLives >= 0) {
        --mLives;
    }
}