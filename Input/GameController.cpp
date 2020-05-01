//
// Created by Hrithvik  Alex on 2020-04-07.
//

#include "GameController.h"
#include "SDL.h"

GameController::GameController(): mMouseMovedAction(nullptr) {}

InputAction GameController::getActionForKey(InputKey key) {
    for(const auto& buttonAction: mButtonActions) {
        if(key == buttonAction.key) {
            return buttonAction.action;
        }
    }

    return [](uint32_t, InputState){};
}

void GameController::addInputActionForKey(const ButtonAction& buttonAction) {
    mButtonActions.push_back(buttonAction);
}

void GameController::clearAll() {
    mButtonActions.clear();
}

bool GameController::IsPressed(InputState state) {
    return state == SDL_PRESSED;

}

bool GameController::IsReleased(InputState state) {
    return state == SDL_RELEASED;
}

InputKey GameController::ActionKey() {
    return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::DKey() {
    return static_cast<InputKey>(SDLK_d);
}

InputKey GameController::CancelKey() {
    return static_cast<InputKey>(SDLK_s);

}
InputKey GameController::ResetKey() {
    return static_cast<InputKey>(SDLK_r);

}
InputKey GameController::LeftKey() {
    return static_cast<InputKey>(SDLK_LEFT);

}
InputKey GameController::RightKey() {
    return static_cast<InputKey>(SDLK_RIGHT);

}
InputKey GameController::UpKey() {
    return static_cast<InputKey>(SDLK_UP);

}
InputKey GameController::DownKey() {
    return static_cast<InputKey>(SDLK_DOWN);
}



MouseInputAction GameController::getMouseButtonActionForButton(MouseButton button) {
    for(const auto& buttonAction: mMouseButtonActions) {
        if(button == buttonAction.mouseButton) {
            return buttonAction.mouseInputAction;
        }
    }

    return [](InputState, const MousePosition&){};
}

void GameController::addMouseButtonAction(const MouseButtonAction& mouseButtonAction) {
    mMouseButtonActions.push_back(mouseButtonAction);
}

MouseButton GameController::LeftMouseButton() {
    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton() {
    return static_cast<MouseButton>(SDL_BUTTON_RIGHT);

}