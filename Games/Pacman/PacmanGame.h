//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANGAME_H
#define LINES_PACMANGAME_H

#include "../Game.h"
#include "PacmanLevel.h"
#include "Pacman.h"
#include "../../graphics/SpriteSheet.h"
#include "../../Input/InputAction.h"

class PacmanGame: public Game {
public:
    void init(GameController& gameController) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;
private:

    void resetGame();
    void updatePacmanMovement();
    void handleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction);
    void drawLives(Screen& screen);

    PacmanMovement mPressedDirection;
    SpriteSheet mPacmanSpriteSheet;
    Pacman mPacman;
    PacmanLevel mLevel;
    size_t mNumLives;

};


#endif //LINES_PACMANGAME_H
