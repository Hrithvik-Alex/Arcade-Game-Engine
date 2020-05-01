//
// Created by Hrithvik  Alex on 2020-04-07.
//

#ifndef LINES_SCENE_H
#define LINES_SCENE_H

#include <string>
#include "../Input/GameController.h"

class Screen;

class Scene {
public:
    virtual ~Scene() {}
    virtual void init() = 0;
    virtual void update(uint32_t dt) = 0;
    virtual void draw(Screen& theScreen) = 0;
    virtual const std::string& getSceneName() const = 0;

    GameController* getGameController() {return &gameController;}
protected:
    GameController gameController;
};

#endif //LINES_SCENE_H
