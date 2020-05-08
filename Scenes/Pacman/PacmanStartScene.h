//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANSTARTSCENE_H
#define LINES_PACMANSTARTSCENE_H

#include "../ButtonOptionsScene.h"

class PacmanStartScene: public ButtonOptionsScene {
public:
    PacmanStartScene();
    void init() override;
    void update(uint32_t dt) override;
    void draw(Screen& theScreen) override;
    const std::string& getSceneName() const override;
private:
};


#endif //LINES_PACMANSTARTSCENE_H
