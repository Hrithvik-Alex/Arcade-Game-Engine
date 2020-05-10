//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMAN_H
#define LINES_PACMAN_H

#include "Actor.h"
#include <stdint.h>


class Screen;
class SpriteSheet;

class Pacman: public Actor {
public:

    virtual void init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = Color::White()) override;
    virtual void update(uint32_t dt) override;
    virtual void setMovementDirection(PacmanMovement direction) override;

    void resetToFirstAnimation();
    void eatenByGhost();
    void resetScore();
    void ateItem(uint32_t value);
    void ateGhost(uint32_t value);


    inline void resetGhostEatenMultiplier() {mGhostMultiplier = 1;}
    inline uint32_t score() const {return mScore;}

private:

    void addToScore(uint32_t value);

    uint32_t mScore;
    uint32_t mGhostMultiplier;
    bool mIsDying;
};


#endif //LINES_PACMAN_H
