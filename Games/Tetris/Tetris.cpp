//
// Created by Hrithvik  Alex on 2020-04-19.
//

#include "Tetris.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"

/*\
 *
 * Game
 *  contains all objects
 *  die when block spawn collides
 *
 * Level
 *  stacks blocks
 *  blocks only disappear after line is filled
 *
 * Scoreboard
 *  line count
 *
 *
 * Tetrominos
 *  7 different kinds
 *  able to rotate
 *  fall at rate
 *  ability to drop instantly
 *  visual indicator of placement
 *
\*/

void Tetris::init(GameController& gameController) {
    gameController.clearAll();

    resetGame();

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mCurrentTetromino->movePosition(Vec2D(-static_cast<float>(Tetromino::BLOCK_WIDTH), 0));
        }
    };

    gameController.addInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mCurrentTetromino->movePosition(Vec2D(Tetromino::BLOCK_WIDTH, 0));
        }
    };

    gameController.addInputActionForKey(rightKeyAction);

    ButtonAction downKeyAction;
    downKeyAction.key = GameController::DownKey();
    downKeyAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mGrid.dropTetromino();
        }
    };

    gameController.addInputActionForKey(downKeyAction);

    ButtonAction leftRotateAction;
    leftRotateAction.key = GameController::ActionKey();
    leftRotateAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mCurrentTetromino->rotateLeft();
        }
    };

    gameController.addInputActionForKey(leftRotateAction);

    ButtonAction rightRotateAction;
    rightRotateAction.key = GameController::DKey();
    rightRotateAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            mCurrentTetromino->rotateRight();
        }
    };

    gameController.addInputActionForKey(rightRotateAction);

    ButtonAction resetKeyAction;
    resetKeyAction.key = GameController::ResetKey();
    resetKeyAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
           resetGame();
        }
    };

    gameController.addInputActionForKey(resetKeyAction);

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            App::Singleton().popScene();
        }
    };

    gameController.addInputActionForKey(backAction);

    mVelocity = 1000;
}

void Tetris::update(uint32_t dt) {
    mCurrentTetromino->update(dt);
    mGrid.update(dt);
    if(mCurrentTetromino->isTetrominoStopped() || mGrid.didCollide()) {
        mCurrentTetromino = mGrid.addToGrid(mVelocity);
        mVelocity *= 0.95;
    }
}

void Tetris::draw(Screen& screen) {
    mCurrentTetromino->draw(screen);
    mGrid.draw(screen);
}

const std::string& Tetris::getName() const {
    static std::string name = "Tetris";
    return name;
}

void Tetris::resetGame() {
    Tetromino* initTetromino = new Tetromino();
    mCurrentTetromino = initTetromino;
    mCurrentTetromino->init({App::Singleton().width()/2.0f, 0});
    Grid grid(mCurrentTetromino);
    mGrid = grid;
    mGrid.init();
}

