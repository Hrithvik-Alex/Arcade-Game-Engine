//
// Created by Hrithvik  Alex on 2020-05-10.
//

#ifndef LINES_GHOST_H
#define LINES_GHOST_H

#include "Actor.h"
#include "../../graphics/color.h"
#include "PacmanGameUtils.h"
#include "../../shapes/Rectangle.h"

enum GhostName {
    BLINKY = 0,
    PINKY,
    INKY,
    CLYDE,
    NUM_GHOSTS
};

enum GhostState {
    GHOST_STATE_ALIVE = 0,
    GHOST_STATE_VULNERABLE,
    GHOST_STATE_VULNERABLE_ENDING,
    GHOST_STATE_DEAD
};

class Ghost: public Actor {
public:

    static const uint32_t VULNERABILITY_TIME = 6000;
    static const uint32_t VULNERABILITY_ENDING_TIME = 4000;

    Ghost();
    virtual void init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = Color::White()) override;
    virtual void update(uint32_t dt) override;

    void setStateToVulnerable();
    virtual void setMovementDirection(PacmanMovement direction) override;
    virtual void stop() override;

    void eatenByPacman();
    void resetToFirstPosition();

    inline bool isDead() const {return mState == GHOST_STATE_DEAD;}
    inline bool isVulnerable() const {return mState == GHOST_STATE_VULNERABLE || mState == GHOST_STATE_VULNERABLE_ENDING;}
    inline bool isAlive() const {return mState == GHOST_STATE_ALIVE;}
    inline uint32_t getPoints() const {return mPoints;}
    inline void lockCanChangeDirection() {mCanChangeDirection = false;}

private:

    void setGhostState(GhostState state);

    uint32_t mVulnerabilityTimer;
    uint32_t mPoints;
    GhostState mState;
    bool mCanChangeDirection;
    Vec2D mInitialPos;
};


#endif //LINES_GHOST_H
