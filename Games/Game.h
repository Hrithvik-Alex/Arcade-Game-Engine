//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_GAME_H
#define LINES_GAME_H

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class Game {
public:
    virtual ~Game(){}
    virtual void init(GameController& gameController) = 0;
    virtual void update(uint32_t dt) = 0;
    virtual void draw(Screen& screen) = 0;
    virtual const std::string& getName() const = 0;
};

#endif //LINES_GAME_H
