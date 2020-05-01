//
// Created by Hrithvik  Alex on 2020-04-09.
//

#include "InputController.h"
#include "GameController.h"
#include "SDL.h"

InputController::InputController(): mQuit(nullptr), mControllerPtr(nullptr) {}

void InputController::init(InputAction quitAction) {
    mQuit = quitAction;

}

void InputController::update(uint32_t dt) {
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT: {
                mQuit(dt, SDL_PRESSED);
            }
            break;

            case SDL_MOUSEMOTION: {
                if (mControllerPtr) {
                    if(MouseMovedAction mouseMoved = mControllerPtr->getMouseMovedAction()) {
                        MousePosition position;
                        position.xPos = sdlEvent.motion.x;
                        position.yPos = sdlEvent.motion.y;
                        mouseMoved(position);
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                if(mControllerPtr) {
                    MouseInputAction action = mControllerPtr->getMouseButtonActionForButton(static_cast<MouseButton>(sdlEvent.button.button));

                    MousePosition position;
                    position.xPos = sdlEvent.button.x;
                    position.xPos = sdlEvent.button.y;

                    action(static_cast<InputState>(sdlEvent.button.state), position);
                }

            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                if (mControllerPtr) {
                    InputAction action = mControllerPtr->getActionForKey(sdlEvent.key.keysym.sym);

                    action(dt, static_cast<InputState>(sdlEvent.key.state));
                }

            }
            break;

        }
    }
}

void InputController::setGameController(GameController* cont) {
    mControllerPtr = cont;
}