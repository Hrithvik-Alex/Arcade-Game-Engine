//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANGAME_H
#define LINES_PACMANGAME_H

#include "../Game.h"

class PacmanGame: public Game {
public:
    void init(GameController& gameController) override;
    void update(uint32_t dt) override;
    void draw(Screen& screen) override;
    const std::string& getName() const override;
private:
};


#endif //LINES_PACMANGAME_H
