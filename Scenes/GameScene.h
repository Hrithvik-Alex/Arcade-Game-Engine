//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_GAMESCENE_H
#define LINES_GAMESCENE_H

#include "Scene.h"
#include "../Games/Game.h"
#include <memory>

class GameScene: public Scene {
public:
    GameScene(std::unique_ptr<Game> gamePtr);
    virtual ~GameScene(){}
    virtual void init() override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& screen) override;

    virtual const std::string& getSceneName() const override;

private:
    std::unique_ptr<Game> mGame;
};

#endif //LINES_GAMESCENE_H
