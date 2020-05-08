//
// Created by Hrithvik  Alex on 2020-04-07.
//

#ifndef LINES_ARCADESCENE_H
#define LINES_ARCADESCENE_H

#include "ButtonOptionsScene.h"
#include <memory>

enum eGame {
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PACMAN,
    NUM_GAMES,
};

class ArcadeScene: public ButtonOptionsScene {
public:
    ArcadeScene();
    virtual void init() override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& theScreen) override;
    virtual const std::string& getSceneName() const override;

private:
    std::unique_ptr<Scene> getScene(eGame game);

};


#endif //LINES_ARCADESCENE_H
