//
// Created by Hrithvik Alex on 2020-05-08.
//

#include "PacmanGame.h"
#include "../../App/App.h"
#include "../../Input/GameController.h"
#include "PacmanGameUtils.h"

namespace {
    const std::string SCORE_STR = "Score   ";
    const std::string PACMAN_LIFE_SPRITE_NAME = "pac_man_left_idle";
    const size_t MAX_NUM_LIVES = 3;
    const uint32_t RELEASE_GHOST_TIME = 5000;
    const std::string READY_STR = "Ready!";
    const std::string GAME_OVER_STR = "Game Over";
    const uint32_t LEVEL_STARTING_TIME = 3000;
}

void PacmanGame::init(GameController& gameController) {

    mReleaseGhostTimer = 0;
    mPacmanSpriteSheet.load("PacmanSprites");
    mPacman.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Pacman_animations.txt", Vec2D::Zero, PACMAN_MOVEMENT_SPEED, false);

    mLevel.init(App::Singleton().getBasePath() + "../Assets/Pacman_level.txt", &mPacmanSpriteSheet);

    mStringRect = Rectangle(Vec2D(0,mLevel.getInGameTextYPos()), App::Singleton().width(), mPacman.getBoundingBox().getHeight());

    setupGhosts();
    resetGame();

    ButtonAction leftAction;
    leftAction.key = GameController::LeftKey();
    leftAction.action = [this](uint32_t dt, InputState state) {
        handleGameControllerState(dt,state,PACMAN_MOVEMENT_LEFT);
    };
    gameController.addInputActionForKey(leftAction);

    ButtonAction rightAction;
    rightAction.key = GameController::RightKey();
    rightAction.action = [this](uint32_t dt, InputState state) {
        handleGameControllerState(dt,state,PACMAN_MOVEMENT_RIGHT);
    };
    gameController.addInputActionForKey(rightAction);

    ButtonAction upAction;
    upAction.key = GameController::UpKey();
    upAction.action = [this](uint32_t dt, InputState state) {
        handleGameControllerState(dt,state,PACMAN_MOVEMENT_UP);
    };
    gameController.addInputActionForKey(upAction);

    ButtonAction downAction;
    downAction.key = GameController::DownKey();
    downAction.action = [this](uint32_t dt, InputState state) {
        handleGameControllerState(dt,state,PACMAN_MOVEMENT_DOWN);
    };
    gameController.addInputActionForKey(downAction);
}

void PacmanGame::update(uint32_t dt) {
    if(mGameState == LEVEL_STARTING) {
        mPacman.resetGhostEatenMultiplier();
        mLevelStartingTimer += dt;

        if(mLevelStartingTimer >= LEVEL_STARTING_TIME) {
            mLevelStartingTimer = 0;
            mGameState = PLAY_GAME;
        }
    } else if(mGameState == PLAY_GAME) {
        updatePacmanMovement();
        mPacman.update(dt);
        mLevel.update(dt, mPacman, mGhosts, mGhostAIs);

        mReleaseGhostTimer += dt;

        for(size_t i = 0; i < NUM_GHOSTS; ++i) {

            Ghost& ghost = mGhosts[i];
            GhostAI& ghostAI = mGhostAIs[i];

            if(mReleaseGhostTimer > RELEASE_GHOST_TIME && ghostAI.isInPen() && !ghost.isReleased()) {
                mReleaseGhostTimer = 0;
                ghost.releaseFromPen();
            }

            auto direction = ghostAI.update(dt, mPacman, mLevel, mGhosts);

            if((ghost.isReleased() && ghost.canChangeDirection()) || (ghost.isReleased() && ghostAI.wantsToLeavePen() && direction != PACMAN_MOVEMENT_NONE)) {
                if(direction != ghost.getMovementDirection()) {
                    ghost.setMovementDirection(direction);
                    ghost.lockCanChangeDirection();
                }
            }

            ghost.update(dt);

            if(ghost.isVulnerable() && mPacman.getEatingBBox().intersects(ghost.getBoundingBox())) {
                ghost.eatenByPacman();
                mPacman.ateGhost(ghost.getPoints());
            } else if(ghost.isAlive() && ghost.getEatingBBox().intersects(mPacman.getBoundingBox())) {
                mNumLives--;
                mGameState = LOST_LIFE;
                mPacman.eatenByGhost();
                mPressedDirection = PACMAN_MOVEMENT_NONE;
                mPacman.setMovementDirection(PACMAN_MOVEMENT_NONE);
                return;
            }
        }

        if(mLevel.isLevelOver()) {
            mLevel.increaseLevel();
            resetLevel();
        }
    } else if(mGameState == LOST_LIFE) {
        mPacman.update(dt);

        if(mPacman.isFinishedAnimation()) {
            if(mNumLives >= 0) {
                resetLevel();
            } else {
                mGameState = GAME_OVER;
            }
        }
    }

}

void PacmanGame::draw(Screen& screen) {
    mLevel.draw(screen);
    mPacman.draw(screen);

    for(auto& ghost : mGhosts) {
        ghost.draw(screen);
    }

    for(auto& ghostAI : mGhostAIs) {
        ghostAI.draw(screen);
    }

    const auto& font = App::Singleton().getFont();
    Vec2D textDrawPosition;

    //Draw Score
    {
        Vec2D levelOffset = mLevel.getLayoutOffset();

        Rectangle highScoreRect = Rectangle(Vec2D(0,4), App::Singleton().width(), levelOffset.GetY());

        std::string scoreStr = std::to_string(mPacman.score());

        textDrawPosition = font.getDrawPosition(SCORE_STR + scoreStr, highScoreRect, BFXA_CENTER, BFYA_CENTER);

        screen.Draw(font, SCORE_STR + scoreStr, textDrawPosition);
    }

    if(mGameState == LEVEL_STARTING) {
        textDrawPosition = font.getDrawPosition(READY_STR, mStringRect, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(font, READY_STR, textDrawPosition, Color::Yellow());
    } else if(mGameState == GAME_OVER) {
        textDrawPosition = font.getDrawPosition(GAME_OVER_STR, mStringRect, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(font, GAME_OVER_STR, textDrawPosition, Color::Yellow());
    }



    drawLives(screen);
}

void PacmanGame::drawLives(Screen &screen) {
    const uint32_t X_PAD = 1;

    auto sprite = mPacmanSpriteSheet.getSprite(PACMAN_LIFE_SPRITE_NAME);

    uint32_t xPosition = X_PAD;

    for(int i = 0; i < mNumLives; ++i) {
        screen.Draw(mPacmanSpriteSheet, PACMAN_LIFE_SPRITE_NAME, Vec2D(xPosition, App::Singleton().height() - sprite.height));
        xPosition += X_PAD + sprite.width;
    }
}

const std::string& PacmanGame::getName() const {
    static std::string name = "!Pacman";
    return name;
}

void PacmanGame::resetGame() {
    mNumLives = MAX_NUM_LIVES;
    mPressedDirection = PACMAN_MOVEMENT_NONE;
    mPacman.resetScore();
    mLevel.resetToFirstLevel();
    resetLevel();
}

void PacmanGame::resetLevel() {

    mGameState = LEVEL_STARTING;
    mPacman.moveTo(mLevel.getPacmanSpawnLocation());
    mPacman.resetToFirstAnimation();

    for(auto& ghost : mGhosts) {
        ghost.resetToFirstPosition();
    }

    mGhosts[BLINKY].releaseFromPen();

}

void PacmanGame::updatePacmanMovement() {
    if(mPressedDirection != PACMAN_MOVEMENT_NONE) {
        if(!mLevel.willCollide(mPacman.getBoundingBox(), mPressedDirection)) {
            mPacman.setMovementDirection(mPressedDirection);
        }
    }
}

void PacmanGame::handleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction) {
    if(GameController::IsPressed(state)) {
        mPressedDirection = direction;
    } else if(GameController::IsReleased(state) && mPressedDirection == direction) {
        mPressedDirection = PACMAN_MOVEMENT_NONE;
    }
}

void PacmanGame::setupGhosts() {

    const Vec2D BLINKY_SCATTER_POSITION = Vec2D(App::Singleton().width() - 24, 0);
    const Vec2D INKY_SCATTER_POSITION = Vec2D(App::Singleton().width(), App::Singleton().height());
    const Vec2D PINKY_SCATTER_POSITION = Vec2D(24,0);
    const Vec2D CLYDE_SCATTER_POSITION = Vec2D(0,App::Singleton().height());

    mGhosts.resize(NUM_GHOSTS);
    mGhostAIs.resize(NUM_GHOSTS);

    Ghost blinky;
    blinky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[BLINKY], GHOST_MOVEMENT_SPEED, true, Color::Red());
    blinky.setMovementDirection(PACMAN_MOVEMENT_LEFT);
    mGhosts[BLINKY] = blinky;

    GhostAI blinkyAI;
    blinkyAI.init(mGhosts[BLINKY], blinky.getBoundingBox().getWidth(), BLINKY_SCATTER_POSITION, mLevel.getGhostSpawnPoints()[PINKY], mLevel.getGhostSpawnPoints()[BLINKY], BLINKY);

    mGhostAIs[BLINKY] = blinkyAI;

    Ghost pinky;
    pinky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[PINKY], GHOST_MOVEMENT_SPEED, true, Color::Pink());
    pinky.setMovementDirection(PACMAN_MOVEMENT_DOWN);
    mGhosts[PINKY] = pinky;

    GhostAI pinkyAI;
    pinkyAI.init(mGhosts[PINKY], blinky.getBoundingBox().getWidth(), PINKY_SCATTER_POSITION, mLevel.getGhostSpawnPoints()[PINKY], mLevel.getGhostSpawnPoints()[BLINKY], PINKY);

    mGhostAIs[PINKY] = pinkyAI;

    Ghost inky;
    inky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[INKY], GHOST_MOVEMENT_SPEED, true, Color::Cyan());
    inky.setMovementDirection(PACMAN_MOVEMENT_UP);
    mGhosts[INKY] = inky;

    GhostAI inkyAI;
    inkyAI.init(mGhosts[INKY], blinky.getBoundingBox().getWidth(), INKY_SCATTER_POSITION, mLevel.getGhostSpawnPoints()[PINKY], mLevel.getGhostSpawnPoints()[BLINKY], INKY);

    mGhostAIs[INKY] = inkyAI;

    Ghost clyde;
    clyde.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[CLYDE], GHOST_MOVEMENT_SPEED, true, Color::Orange());
    clyde.setMovementDirection(PACMAN_MOVEMENT_RIGHT);
    mGhosts[CLYDE] = clyde;

    GhostAI clydeAI;
    clydeAI.init(mGhosts[CLYDE], blinky.getBoundingBox().getWidth(), CLYDE_SCATTER_POSITION, mLevel.getGhostSpawnPoints()[PINKY], mLevel.getGhostSpawnPoints()[BLINKY], CLYDE);

    mGhostAIs[CLYDE] = clydeAI;

    for(size_t i = 0; i < NUM_GHOSTS; ++i) {
        mGhosts[i].setGhostDelegate(mGhostAIs[i]);
    }
}