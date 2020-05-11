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
}

void PacmanGame::init(GameController& gameController) {

    mPacmanSpriteSheet.load("PacmanSprites");
    mPacman.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Pacman_animations.txt", Vec2D::Zero, PACMAN_MOVEMENT_SPEED, false);

    mLevel.init(App::Singleton().getBasePath() + "../Assets/Pacman_level.txt", &mPacmanSpriteSheet, &mPacman);

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
    updatePacmanMovement();
    mPacman.update(dt);
    mLevel.update(dt);

    for(size_t i = 0; i < NUM_GHOSTS; ++i) {
        mGhosts[i].update(dt);
    }

    if(mLevel.isLevelOver()) {
        mLevel.increaseLevel();
    }
}

void PacmanGame::draw(Screen& screen) {
    mLevel.draw(screen);
    mPacman.draw(screen);

    for(auto& ghost : mGhosts) {
        ghost.draw(screen);
    }

    //Draw Score
    {
        Vec2D levelOffset = mLevel.getLayoutOffset();

        Rectangle highScoreRect = Rectangle(Vec2D(0,4), App::Singleton().width(), levelOffset.GetY());

        const auto& font = App::Singleton().getFont();
        Vec2D textDrawPosition;

        std::string scoreStr = std::to_string(mPacman.score());

        textDrawPosition = font.getDrawPosition(SCORE_STR + scoreStr, highScoreRect, BFXA_CENTER, BFYA_CENTER);

        screen.Draw(font, SCORE_STR + scoreStr, textDrawPosition);

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
    mGhosts.resize(NUM_GHOSTS);

    Ghost blinky;
    blinky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[BLINKY], GHOST_MOVEMENT_SPEED, true, Color::Red());
    blinky.setMovementDirection(PACMAN_MOVEMENT_LEFT);
    mGhosts[BLINKY] = blinky;

    Ghost pinky;
    pinky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[PINKY], GHOST_MOVEMENT_SPEED, true, Color::Pink());
    pinky.setMovementDirection(PACMAN_MOVEMENT_DOWN);
    mGhosts[PINKY] = pinky;

    Ghost inky;
    inky.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[INKY], GHOST_MOVEMENT_SPEED, true, Color::Cyan());
    inky.setMovementDirection(PACMAN_MOVEMENT_UP);
    mGhosts[INKY] = inky;

    Ghost clyde;
    clyde.init(mPacmanSpriteSheet, App::Singleton().getBasePath() + "../Assets/Ghost_animations.txt", mLevel.getGhostSpawnPoints()[CLYDE], GHOST_MOVEMENT_SPEED, true, Color::Orange());
    clyde.setMovementDirection(PACMAN_MOVEMENT_RIGHT);
    mGhosts[CLYDE] = clyde;
}