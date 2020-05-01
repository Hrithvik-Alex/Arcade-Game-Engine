//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_INPUTCONTROLLER_H
#define LINES_INPUTCONTROLLER_H

#include "InputAction.h"

class GameController;

class InputController {
public:
    InputController();
    void init(InputAction quitAction);
    void update(uint32_t dt);

    void setGameController(GameController* cont);

private:
    InputAction mQuit;
    GameController* mControllerPtr;
};

#endif //LINES_INPUTCONTROLLER_H
