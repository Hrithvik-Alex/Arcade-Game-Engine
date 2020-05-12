//
// Created by Hrithvik  Alex on 2020-05-10.
//

#include "Ghost.h"

namespace {
    const uint32_t NUM_POINTS_FOR_GHOST = 200;
}


Ghost::Ghost(): mPoints(0), mInitialPos(Vec2D::Zero), mIsReleased(false), mDelegate(nullptr) {}

void Ghost::init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor) {
    Actor::init(spriteSheet,animationsPath,initialPos,movementSpeed,updateSpriteOnMovement,spriteColor);
    mInitialPos = initialPos;
    mPoints = NUM_POINTS_FOR_GHOST;
    resetToFirstPosition();
}

void Ghost::update(uint32_t dt) {
    Vec2D pos = position();

    Actor::update(dt);

    mCanChangeDirection = pos != position();

    if(isVulnerable()) {
        mVulnerabilityTimer += dt;

        if(mState == GHOST_STATE_VULNERABLE && mVulnerabilityTimer >= VULNERABILITY_TIME) {
            setGhostState(GHOST_STATE_VULNERABLE_ENDING);
        }

        if(mState == GHOST_STATE_VULNERABLE_ENDING && mVulnerabilityTimer >= VULNERABILITY_ENDING_TIME) {
            setGhostState(GHOST_STATE_ALIVE);
        }
    }
}

void Ghost::setStateToVulnerable() {
    if(mState != GHOST_STATE_DEAD) {
        setGhostState(GHOST_STATE_VULNERABLE);
    }
}

void Ghost::setMovementDirection(PacmanMovement direction) {
    Actor::setMovementDirection(direction);

    PacmanMovement movementDir = getMovementDirection();

    if(mState == GHOST_STATE_ALIVE) {
        if(movementDir == PACMAN_MOVEMENT_RIGHT) {
            setAnimation("ghost_movement_right", true);
        } else if(movementDir == PACMAN_MOVEMENT_UP) {
            setAnimation("ghost_movement_up", true);
        } else if(movementDir == PACMAN_MOVEMENT_DOWN) {
            setAnimation("ghost_movement_down", true);
        } else if(movementDir == PACMAN_MOVEMENT_LEFT) {
            setAnimation("ghost_movement_left", true);
        }
    } else if(mState == GHOST_STATE_DEAD) {
        if(movementDir == PACMAN_MOVEMENT_RIGHT) {
            setAnimation("ghost_dead_right", true);
        } else if(movementDir == PACMAN_MOVEMENT_UP) {
            setAnimation("ghost_dead_up", true);
        } else if(movementDir == PACMAN_MOVEMENT_DOWN) {
            setAnimation("ghost_dead_down", true);
        } else if(movementDir == PACMAN_MOVEMENT_LEFT) {
            setAnimation("ghost_dead_left", true);
        }
    }
}

void Ghost::stop() {
    setMovementDirection(PACMAN_MOVEMENT_NONE);
}

void Ghost::eatenByPacman() {
    setGhostState(GHOST_STATE_DEAD);
}

void Ghost::resetToFirstPosition() {
    mSprite.setPosition(mInitialPos);
    setMovementDirection(PACMAN_MOVEMENT_NONE);
    mVulnerabilityTimer = 0;
    setGhostState(GHOST_STATE_ALIVE);
    mCanChangeDirection = true;
    mIsReleased = false;

    if(mDelegate) {
        mDelegate->GhostWasResetToFirstPosition();
    }
}

void Ghost::setGhostState(GhostState state) {

    if(mDelegate) {
        mDelegate->GhostDelegateGhostStateChangedTo(mState, state);
    }

    mState = state;
    switch(mState) {
        case GHOST_STATE_ALIVE: {
            setMovementDirection(getMovementDirection());
            setMovementSpeed(GHOST_MOVEMENT_SPEED);
            break;
        }
        case GHOST_STATE_VULNERABLE: {
            mSprite.setAnimation("ghost_vulnerable", true);
            mVulnerabilityTimer = 0;
            setMovementSpeed(GHOST_VULNERABLE_MOVEMENT_SPEED);
            break;
        }
        case GHOST_STATE_VULNERABLE_ENDING: {
            mSprite.setAnimation("ghost_vulnerable_ending", true);
            mVulnerabilityTimer = 0;
            break;
        }
        case GHOST_STATE_DEAD: {
            setMovementDirection(getMovementDirection());
            setMovementSpeed(GHOST_BACK_TO_PEN_SPEED);
            break;
        }

    }
}

void Ghost::releaseFromPen() {
    mIsReleased = true;

    if(mDelegate) {
        mDelegate->GhostWasReleasedFromPen();
    }
}