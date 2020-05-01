//
// Created by Hrithvik  Alex on 2020-04-28.
//

#ifndef LINES_NOTIMPLEMENTEDSCENE_H
#define LINES_NOTIMPLEMENTEDSCENE_H

#include "Scene.h"

class Screen;

class NotImplementedScene: public Scene {
public:
    virtual void init() override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& theScreen) override;
    virtual const std::string& getSceneName() const override;
private:
};


#endif //LINES_NOTIMPLEMENTEDSCENE_H
