//
// Created by Hrithvik  Alex on 2020-05-08.
//

#include "PacmanGame.h"
#include "../../App/App.h"

void PacmanGame::init(GameController& gameController) {
    mLevel.init(App::Singleton().getBasePath() + "../Assets/Pacman_level.txt");
}

void PacmanGame::update(uint32_t dt) {
    mLevel.update(dt);
}

void PacmanGame::draw(Screen& screen) {
    mLevel.draw(screen);
}

const std::string& PacmanGame::getName() const {
    static std::string name = "!Pacman";
    return name;
}

